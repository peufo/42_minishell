#include "minishell.h"

void	func_Q1(t_lexer *lexer)
{
	lexer->cursor++;
	if (lexer->cursor == '\'')
		tokenise_single_quote(lexer);
	if (lexer->cursor == '"')	
		func_Q2(lexer);
	else

		(void)lexer;
}

void	func_Q2(t_lexer *lexer)
{
	lexer->cursor++;
}

void	func_Q3(t_lexer *lexer)
{
	lexer->cursor++;
}

void	func_Q4(t_lexer *lexer)
{
	lexer->cursor++;
}

void	func_Q5(t_lexer *lexer)
{
	lexer->cursor++;
}
