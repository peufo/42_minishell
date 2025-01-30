/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_and_var.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:23:04 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 15:14:58 by jvoisard         ###   ########.fr       */
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

void	lexer_process_word(t_lexer *lexer)
{
	char	*start;

	start = lexer->cursor;
	while (*lexer->cursor && !ft_isspace(*lexer->cursor) && !ft_strchr("()|><"
			, *lexer->cursor))
		lexer->cursor++;
	lexer_add_token(lexer, TOKEN_WORD, ft_substr(start, 0, lexer->cursor - start));
}

void	lexer_process_single_quote(t_lexer *lexer)
{
	char	*start;

	if (*lexer->cursor != '\'')
		return ;
	start = ++lexer->cursor;
	while (*lexer->cursor && *lexer->cursor != '\'')
		lexer->cursor++;
	if (*lexer->cursor == '\'')
	{
		lexer_add_token(lexer, TOKEN_WORD, ft_substr(start, 0,
				lexer->cursor - start));
		lexer->cursor++;
	}
	else
		throw_error("Unclosed single quote", WHERE);
}

void	lexer_process_double_quote(t_lexer *lexer)
{
	char	*i;

	if (*lexer->cursor != '"')
		return ;
	i = ++lexer->cursor;
	while (*lexer->cursor && *lexer->cursor != '"')
	{
		if (*lexer->cursor == '$')
		{
			lexer_add_token(lexer, TOKEN_WORD, ft_substr(i, 0, lexer->cursor - i));
			lexer_process_variable(lexer);
			i = lexer->cursor;
		}
		else
			lexer->cursor++;
	}
	if (*lexer->cursor == '"')
	{
		if (lexer->cursor > i)
			lexer_add_token(lexer, TOKEN_WORD, ft_substr(i, 0, lexer->cursor - i));
		lexer->cursor++;
	}
	else
		throw_error("Unclosed double quote", WHERE);
}

void	lexer_process_variable(t_lexer *lexer)
{
	char	*start;
	char	*value;

	if (*lexer->cursor != '$')
		return ;
	start = ++lexer->cursor;
	lexer->len = 0;
	if (start[0] == '?')
		return (lexer_process_status(lexer, start));
	while (ft_isalnum(start[lexer->len]) || start[lexer->len] == '_')
		lexer->len++;
	if (lexer->len > 0)
	{
		lexer->varname = ft_substr(start, 0, lexer->len);
		value = getenv(lexer->varname);
		if (value)
			lexer_add_token(lexer, TOKEN_VAR, ft_strdup(value));
		else
			lexer_add_token(lexer, TOKEN_VAR, ft_strdup(""));
		free(lexer->varname);
	}
	lexer->cursor += lexer->len;
	lexer->varname = NULL;
}
