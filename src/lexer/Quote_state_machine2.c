#include "minishell.h"

void	func_D1(t_lexer *lexer)
{
	lexer->cursor++;
	if (lexer->state != S0 && lexer->state != D4)
		tokenise_double_quote(lexer);
	lexer->state = D1;
	if (lexer->cursor == '"')
		look_for_quotes(lexer);
	else if (lexer->cursor == '\'')
		func_D2(lexer);
	else if (lexer->cursor == '$')
		func_D4(lexer);
	else
		func_D3(lexer);	
}

void	func_D2(t_lexer *lexer)
{
	lexer->cursor++;
	lexer->state = D2;
	if (lexer->cursor == '\'')
		func_D1(lexer);
	else if (lexer->cursor == '"')
		look_for_quotes(lexer);
	else if (lexer->cursor != '\'' && lexer->cursor != '"')
		func_D3(lexer);
	else if (lexer->cursor != '\'')
		func_D2(lexer);
}

void	func_D3(t_lexer *lexer)
{
	lexer->cursor++;
	lexer->state = D3;
	if (lexer->cursor == '\'')	
		func_D1(lexer);
	else if (lexer->cursor == '"')
		look_for_quotes(lexer);
	else if (lexer->cursor != '\'' && lexer->cursor != '"')
		func_D3(lexer);
}

void	func_D4(t_lexer *lexer)
{
	lexer->cursor++;
	if (lexer->state == D5)
		tokenise_variable(lexer);
	lexer->state = D4;
	if (ft_isdigit(lexer->cursor))
		func_D1(lexer);
	else if (lexer->cursor == '"')
		look_for_quotes(lexer);
	else if (lexer->cursor != '\'' && lexer->cursor != '$')
		func_D5(lexer);
}

void	func_D5(t_lexer *lexer)
{
	lexer->cursor++;
	lexer->state = D5;
	if (lexer->cursor != '"' && lexer->cursor != '$')
		func_D5(lexer);
	else if (lexer->cursor == '$')
		func_D4(lexer);
	else if (lexer->cursor == '"')
		look_for_quotes(lexer);
}
