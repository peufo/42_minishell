#include "minishell.h"

void	add_marker(t_lexer *lexer)
{
	char	*marker;

	if (!lexer || !lexer->cursor)
	{
		message(NULL_STRING, ADD_MARKER);
		return ;
	}
	marker = lexer->cursor;
	ft_lstadd_back(&lexer->starters, ft_lstnew(marker));
}

void	process_status(t_lexer *lexer, char *start)
{
	pid_t	status;

	while (ft_isalnum(start[lexer->len]) || start[lexer->len] == '?')
		lexer->len++;
	if (lexer->len > 0)
	{
		lexer->varname = ft_substr(start, 0, lexer->len);
		status = get_the_pid(lexer->varname);
		free(lexer->varname);
		if (status)
		{
			lexer->varname = ft_itoa(status);
			lexer_add_token(lexer, L_PID, lexer->varname);
			free(lexer->varname);
		}
		else
			lexer_add_token(lexer, L_PID, ft_strdup("0"));
	}
	lexer->cursor += lexer->len;
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (*lexer->cursor && ft_isspace(*lexer->cursor))
		lexer->cursor++;
}

void	lexer_skip_comment(t_lexer *lexer)
{
	if (*lexer->cursor == '#')
	{
		while (*lexer->cursor)
			lexer->cursor++;
	}
}

void	lexer_add_token(t_lexer *lexer, int type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return ;
	token->type = type;
	token->value.value = ft_strdup(value);
	if (!token->value.value)
	{
		free(token);
		return ;
	}
	ft_lstadd_back(&lexer->tokens, ft_lstnew(token));
}

void	lex_free(t_sh *shell)
{
	t_list	*current;
	t_list	*next;
	t_token	*token;
	t_lexer	*lexer;

	lexer = &shell->lexer;
	if (!lexer || !lexer->tokens)
		return ;
	current = lexer->tokens;
	while (current)
	{
		next = current->next;
		token = (t_token *)current->content;
		if (token)
		{
			if (token->value.value)
				free(token->value.value);
			free(token);
		}
		free(current);
		current = next;
	}
	lexer->tokens = NULL;
}
