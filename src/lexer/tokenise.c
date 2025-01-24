#include "minishell.h"
#include "macros.h"


void 	tokenise_parenthesis(t_sh *shell)
{
	t_token 	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		message(MALLOC_ERROR, TOKEN_PARENTHESIS);
		return ;
	}
	string_free(&token->value);
	token->value.value = ft_strdup("");
	if (*shell->lexer.cursor == '(' || *shell->lexer.cursor == ')')
	{
		token->value.value = ft_strdup(*shell->lexer.cursor);
		shell->lexer.cursor++;
	}
	ft_lstadd_back(&shell->lexer.tokens, ft_lstnew(token));

}

void 	tokenise_quotes(t_sh *shell)
{
	t_token		*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		message(MALLOC_ERROR, TOKENISE_QUOTES);
		return ;
	}
	string_free(&token->value);
	token->value.value = ft_strdup("");
	shell->lexer.cursor++;
	while (*shell->lexer.cursor && *shell->lexer.cursor != '"')
	{
		string_push(&token->value, &shell->lexer.cursor);
		shell->lexer.cursor++;
	}
	if (*shell->lexer.cursor == '"')
		shell->lexer.cursor++;
	ft_lstadd_back(&shell->lexer.tokens, ft_lstnew(token));
}

void 	tokenise_gates(t_sh *shell)
{
	t_token		*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		message(MALLOC_ERROR, TOKENISE_GATES);
		return ;
	}
	string_free(&token->value);
	token->value.value = ft_strdup("");
	if (*shell->lexer.cursor == '&')
	{
		shell->lexer.cursor++;
		if (*shell->lexer.cursor == '&')
			add_to_list(shell, token, '&');
		return ;
	}
	else if (*shell->lexer.cursor == '|')
	{
		shell->lexer.cursor++;
		if (*shell->lexer.cursor == '|')
			add_to_list(shell, token, '|');
		return ;
	}
	ft_lstadd_back(&shell->lexer.tokens, ft_lstnew(token));
}

void 	tokenise_variable(t_sh *shell)
{
	t_token 	*token;

	token = malloc(sizeof(token));
	if (!token)
	{
		message(MALLOC_ERROR, TOKENISE_VARIABLE);
		return ;
	}
	string_free(&token->value);
	token->value.value = ft_strdup("");
	shell->lexer.cursor++;
	while (*shell->lexer.cursor && ft_isalphanum(*shell->lexer.cursor))
		string_push_and_go(shell, token);
	ft_lstadd_back(&shell->lexer.cursor, ft_lstnew(token));
}

////////////
// 	TODO ///
/////////// 
void 	tokenise_redirection(t_sh *shell)
{
	t_token 	*token;
	
	token = malloc(sizeof(t_token));
	if (!token)
	{
		message(MALLOC_ERROR, TOKENISE_DIRECTION);
		return ;
	}
	return ;
	if (*shell->lexer.cursor == '>')
	{
		if (shell->lexer.cursor[1] == '>')
			return ;
	}
}