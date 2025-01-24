#include "minishell.h"

void 	string_push_and_go(t_sh *shell, t_token *token)
{
	string_push(&token->value, *shell->lexer.cursor);
	shell->lexer.cursor++;
}

void 	add_to_list(t_sh *shell, t_token *token, int c)
{
	if (c == AND_GATE)
	{
		string_push(&token->value, '&');
		string_push(&token->value, '&');
	}
	else if (c == OR_GATE)
	{
		string_push(&token->value, '|');
		string_push(&token->value, '|');
	}
	else
		string_push(&token->value, (char)c);
	ft_lstadd_back(&shell->lexer.tokens, ft_lstnew(token));
	shell->lexer.cursor++;
}
