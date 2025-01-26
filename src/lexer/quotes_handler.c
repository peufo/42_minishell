#include "minishell.h"

static void	ignore_comment(t_lexer *lexer)
{
	while (lexer->cursor)
		lexer->cursor++;
}

static void	func_V1(t_lexer *lexer)
{
	(void)lexer;
}

void	look_for_quotes(t_lexer *lexer)
{
	if (lexer->state != S0 && lexer->cursor == '"')
		tokenise_double_quote(lexer);
	else if (lexer->state != S0 && lexer->cursor == '\'')
		tokenise_single_quote(lexer);
	else if (lexer->state != S0 && &lexer->cursor[(int)ft_lstlast(lexer->starters)] == '$')
		tokenise_variable(lexer);
	lexer->state = S0;
	if (lexer->cursor == '#')
		ignore_comment(lexer);
	else if (lexer->cursor == '\'')
		func_Q1(lexer);
	else if (lexer->cursor == '"')
		func_D1(lexer);
	else if (lexer->cursor == '$')
		func_V1(lexer);
}
