#include "minishell.h"

void	func_Q1(t_lexer *lexer)
{
	lexer->cursor++;
	if (lexer->state != S0)
		tokenise_single_quote(lexer);
	lexer->state = Q1;
	if (lexer->cursor != '\'')
		func_D2(lexer);
}

void	func_Q2(t_lexer *lexer)
{
	lexer->cursor++;
	lexer->state = Q2;
	if (lexer->cursor != '\'')
		func_Q2(lexer);
	else
		look_for_quotes(lexer);
}
