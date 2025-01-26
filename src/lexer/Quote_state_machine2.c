#include "minishell.h"

void	func_D1(t_lexer *lexer)
{
	lexer->cursor++;
	lexer->state = D1;
	if (lexer->cursor == '"')
		tokenise_double_quote(lexer);
	else if (lexer->cursor == '\'')
		func_D2(lexer);
	else if (lexer->cursor == '$')
		func_D4(lexer);
	
		
}

void	func_D2(t_lexer *lexer)
{
	lexer->cursor++;
}

void	func_D3(t_lexer *lexer)
{
	lexer->cursor++;
}

void	func_D4(t_lexer *lexer)
{
	lexer->cursor++;
}

void	func_D5(t_lexer *lexer)
{
	lexer->cursor++;
}
