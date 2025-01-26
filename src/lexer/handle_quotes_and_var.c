#include "minishell.h"
/*
static void	ignore_comment(t_lexer *lexer)
{
	while (*lexer->cursor)
	{
		lexer->cursor++;
	}
}

static void	func_V1(t_lexer *lexer)
{
	if (!lexer || !lexer->cursor || !*(lexer->cursor))
		return ;
//	get all env variable
}

void	look_for_quotes(t_lexer *lexer)
{
	if (lexer->state == S1)
		tokenise_variable(lexer);
	else if (lexer->state != S0 && *lexer->cursor == '"')
		tokenise_quote(lexer);
	else if (lexer->state != S0 && *lexer->cursor == '\'')
		tokenise_quote(lexer);
	lexer->state = S0;
	if (*lexer->cursor == '#')
		ignore_comment(lexer);
	else if (*lexer->cursor == '\'')
		func_Q1(lexer);
	else if (*lexer->cursor == '"')
		func_D1(lexer);
	else if (*lexer->cursor == '$')
		func_V1(lexer);
}
*/

void	lexer_process_word(t_lexer *lexer)
{
	char	*start;

	start = lexer->cursor;
	while (*lexer->cursor && !ft_isspace(*lexer->cursor) && !ft_strchr("()|><"
			, *lexer->cursor))
		lexer->cursor++;
	lexer_add_token(lexer, L_WORD, ft_substr(start, 0, lexer->cursor - start));
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
		lexer_add_token(lexer, L_WORD, ft_substr(start, 0,
				lexer->cursor - start));
		lexer->cursor++;
	}
	else
		message(UNMATCHED_QUOTE, TOKENISE_QUOTES);
}

void	lexer_process_double_quote(t_lexer *lexer)
{
	char	*start;

	if (*lexer->cursor != '"')
		return ;
	start = ++lexer->cursor;
	while (*lexer->cursor && *lexer->cursor != '"')
	{
		if (*lexer->cursor == '$')
		{
			lexer_add_token(lexer, L_WORD, ft_substr(start, 0,
					lexer->cursor - start));
			lexer_process_variable(lexer);
			start = lexer->cursor;
		}
		else
			lexer->cursor++;
	}
	if (*lexer->cursor == '"')
	{
		if (lexer->cursor > start)
			lexer_add_token(lexer, L_WORD, ft_substr(start, 0,
					lexer->cursor - start));
		lexer->cursor++;
	}
	else
		message(UNMATCHED_QUOTE, TOKENISE_QUOTES);
}

void	lexer_process_variable(t_lexer *lexer)
{
	char	*start;
	char	*varname;
	char	*value;
	size_t	len;

	if (*lexer->cursor != '$')
		return ;
	start = ++lexer->cursor;
	len = 0;
	while (ft_isalnum(start[len]) || start[len] == '_')
		len++;
	if (len > 0)
	{
		varname = ft_substr(start, 0, len);
		value = getenv(varname);
		if (value)
			lexer_add_token(lexer, L_VAR, ft_strdup(value));
		else
			lexer_add_token(lexer, L_VAR, ft_strdup(""));
		free(varname);
	}
	lexer->cursor += len;
}
