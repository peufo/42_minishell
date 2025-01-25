#include "minishell.h"
#include "macros.h"


void	tokenise_parenthesis(t_sh *shell)
{
	char	temp[2];
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		message(MALLOC_ERROR, TOKEN_PARENTHESIS);
		return;
	}
	token->value.value = NULL;
	token->value.len = 0;
	if (*shell->lexer.cursor == '(' || *shell->lexer.cursor == ')')
	{
		temp[0] = *shell->lexer.cursor;
		temp[1] = '\0';
		string_push(&token->value, temp[0]);
		shell->lexer.cursor++;
	}
	ft_lstadd_back(&shell->lexer.tokens, ft_lstnew(token));
}

void	tokenise_quotes(t_sh *shell)
{
	t_token	*token;
    char	quote;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		message(MALLOC_ERROR, TOKENISE_QUOTES);
		return ;
	}
	token->value.value = NULL;
	token->value.len = 0;
	string_free(&token->value);
	quote = *shell->lexer.cursor;
	shell->lexer.cursor++;
	while (*shell->lexer.cursor && *shell->lexer.cursor != quote)
	{
		if (string_push(&token->value, *shell->lexer.cursor) != STRING_SUCCESS)
		{
			message(MALLOC_ERROR, TOKENISE_QUOTES);
			string_free(&token->value);
			free(token);
			return ;
		}
		shell->lexer.cursor++;
	}
	if (*shell->lexer.cursor == quote)
		shell->lexer.cursor++;
	ft_lstadd_back(&shell->lexer.tokens, ft_lstnew(token));
}

void	tokenise_gates(t_sh *shell)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		message(MALLOC_ERROR, TOKENISE_GATES);
		return ;
	}
	token->value.value = NULL;
	token->value.len = 0;
	if (*shell->lexer.cursor == '&' && *(shell->lexer.cursor + 1) == '&')
	{
		string_push(&token->value, '&');
		string_push(&token->value, '&');
		shell->lexer.cursor += 2;
	}
	else if (*shell->lexer.cursor == '|' && *(shell->lexer.cursor + 1) == '|')
	{
		string_push(&token->value, '|');
		string_push(&token->value, '|');
		shell->lexer.cursor += 2;
	}
	ft_lstadd_back(&shell->lexer.tokens, ft_lstnew(token));
}

void	tokenise_variable(t_sh *shell)
{
    t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		message(MALLOC_ERROR, TOKENISE_VARIABLE);
		return ;
	}
	string_free(&token->value);
	token->value.value = ft_strdup("");
	if (*shell->lexer.cursor == '$')
	{
		string_push(&token->value, '$');
		shell->lexer.cursor++;
		while (*shell->lexer.cursor && (ft_isalnum(*shell->lexer.cursor) || *shell->lexer.cursor == '_'))
		{
			string_push(&token->value, *shell->lexer.cursor);
			shell->lexer.cursor++;
		}
	}
	ft_lstadd_back(&shell->lexer.tokens, ft_lstnew(token));
}

void	tokenise_redirection(t_sh *shell)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		message(MALLOC_ERROR, TOKENISE_DIRECTION);
		return ;
	}
	token->value.value = NULL;
	token->value.len = 0;
	if (*shell->lexer.cursor == '>' && *(shell->lexer.cursor + 1) == '>')
	{
		string_push(&token->value, '>');
		string_push(&token->value, '>');
		shell->lexer.cursor += 2;
	}
	else if (*shell->lexer.cursor == '<' && *(shell->lexer.cursor + 1) == '<')
	{
		string_push(&token->value, '<');
		string_push(&token->value, '<');
		shell->lexer.cursor += 2;
	}
	else if (*shell->lexer.cursor == '>')
	{
		string_push(&token->value, '>');
		shell->lexer.cursor++;
	}
	else if (*shell->lexer.cursor == '<')
	{
		string_push(&token->value, '<');
		shell->lexer.cursor++;
	}
	ft_lstadd_back(&shell->lexer.tokens, ft_lstnew(token));
}