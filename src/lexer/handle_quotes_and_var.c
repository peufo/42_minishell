/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_and_var.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:23:04 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 15:37:32 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	get_the_pid(char *process)
{
	if (process != NULL)
		return (getpid());
	else
		return (0);
}

void	lexer_process_word(t_sh *shell)
{
	char	*start;

	debug(shell, "\n INTO PROCESS WORD \n");
	start = shell->lex.cursor;
	while (*shell->lex.cursor && !ft_isspace(*shell->lex.cursor)
		&& !ft_strchr("()|><", *shell->lex.cursor))
		shell->lex.cursor++;
	lexer_add_token(T_WORD, ft_cut(start, shell->lex.cursor), shell);
}

void	lexer_process_single_quote(t_sh *shell)
{
	char	*start;

	if (*shell->lex.cursor != '\'')
		return ;
	debug(shell, "\n INTO PROCESS SQUOTE \n");
	start = ++shell->lex.cursor;
	while (*shell->lex.cursor && *shell->lex.cursor != '\'')
		shell->lex.cursor++;
	if (*shell->lex.cursor == '\'')
	{
		lexer_add_token(T_WORD, ft_substr(start, 0,
				shell->lex.cursor - start), shell);
		shell->lex.cursor++;
	}
	else
		throw_error("Unclosed single quote", __FILE__, __LINE__);
}

void	lexer_process_double_quote(t_sh *shell)
{
	char	*i;

	if (*shell->lex.cursor != '"')
		return ;
	i = ++shell->lex.cursor;
	while (*shell->lex.cursor && *shell->lex.cursor != '"')
	{
		if (*shell->lex.cursor == '$')
		{
			lexer_add_token(T_WORD, ft_cut(i, shell->lex.cursor),
				shell);
			lexer_process_variable(shell);
			i = shell->lex.cursor;
		}
		else
			shell->lex.cursor++;
	}
	if (*shell->lex.cursor == '"')
	{
		if (shell->lex.cursor > i)
			lexer_add_token(T_WORD, ft_cut(i, shell->lex.cursor), shell);
		shell->lex.cursor++;
	}
	else
		throw_error("Unclosed double quote", __FILE__, __LINE__);
}

void	lexer_process_variable(t_sh *shell)
{
	char	*start;
	char	*value;

	if (*shell->lex.cursor != '$')
		return ;
	debug(shell, "\n INTO PROCESS VARIABLE \n");
	start = ++shell->lex.cursor;
	shell->lex.len = 0;
	if (start[0] == '?')
		return (lexer_process_status(start, shell));
	while (ft_isalnum(start[shell->lex.len]) || start[shell->lex.len] == '_')
		shell->lex.len++;
	if (shell->lex.len > 0)
	{
		shell->lex.varname = ft_substr(start, 0, shell->lex.len);
		value = getenv(shell->lex.varname);
		if (value)
			lexer_add_token(TOKEN_VAR, ft_strdup(value), shell);
		else
			lexer_add_token(TOKEN_VAR, ft_strdup(""), shell);
		free(shell->lex.varname);
	}
	shell->lex.cursor += shell->lex.len;
	shell->lex.varname = NULL;
}
