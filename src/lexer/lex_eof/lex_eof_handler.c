/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 07:42:21 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/19 10:24:52 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sub_last_token(t_sh *shell, char *new_token)
{
	int	i;

	i = 0;
	while (shell->lexer.tokens[i] != NULL)
		i++;
	free(shell->lexer.tokens[i - 1]);
	shell->lexer.tokens[i - 1] = ft_strdup(new_token);
	free(new_token);
}

static bool	is_eof_token(char *s, int iter)
{
	
	if ((s[iter] == '"' && !s[iter + 1]) || (s[iter] == '\'' && !s[iter + 1]))
		return (true);
	else if (s[iter + 1] == '<' && s[iter] == '<'  && !s[iter + 2])
		return (true);
	return (false);
}

static bool	check_cursor(t_sh *shell)
{
	int		i;
	char	*line;

	i = 0;
	line = shell->lexer.cursor;
	if (!line)
		return (BASIC_MOD);
	printf("line is :%s\n", line);
	if (1)
		return (BASIC_MOD);
	while (line[i] && ft_isalnum(line[i]) && ft_isspace(line[i]))
	{
		if (is_eof_token(line, i))
			return (BONUS_MOD);
		i++;
	}
	return (BASIC_MOD);
}

static bool	check_end_in_line(char *line)
{
	return ((line));
}

static void	stack_new_line(const char **buffer, t_list *toks, char ***new_token)
{
	(void)buffer;
	(void)toks;
	(void)new_token;
}

static void	process_quotes_and_var(t_lexer *lexer)
{
	if (*lexer->cursor == '\'')
		lexer_process_single_quote(lexer);
	else if (*lexer->cursor == '"')
		lexer_process_double_quote(lexer);
	else if (*lexer->cursor == '$')
		lexer_process_variable(lexer);
	else if (!ft_isspace(*lexer->cursor) && !ft_strchr("()|><", *lexer->cursor))
		lexer_process_word(lexer);
}

void	lex_eof_free(t_sh *shell, t_lexer *lex)
{
	(void)lex;
	if (shell->lexer.tokens)
		string_array_free(&shell->lexer.tokens);
	//	free temp lex

}

static bool	handle_hard_start(t_sh *shell, t_lexer *lex)
{
	(void)shell;
	(void)lex;
}

void	lex_eof(t_sh *shell, t_lexer *lex)
{
	char		*buffer;
	char		**new_token;

	buffer = NULL;
	new_token = NULL;
	if (!lex_eof_check_init(shell))
		return ;
	while (1)
	{
		lex->cursor = readline('>');
		if (!lex->cursor)
			shell_exit(shell);
		errno = false;
		while (*(lex->cursor))
			process_quotes_and_var(lex);
		stack_new_line(&buffer, lex->tokens, &new_token);
		add_history(buffer);
		free(buffer);
		if (check_end_in_line(lex->cursor))
			break ;
	}
	if (shell->lexer.tokens)
		sub_last_token(shell, *new_token);
	else
		shell->lexer.tokens = string_array_dup(new_token);
	return (string_array_free(&new_token));
}

bool	lex_check_eof(t_sh *shell)
{
	(void)shell;
}
