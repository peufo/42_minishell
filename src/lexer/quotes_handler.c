#include "minishell.h"

static void	ignore_comment(t_lexer *lexer)
{
	while (lexer->cursor)
		lexer->cursor++;
}

void	look_for_quotes(t_lexer *lexer)
{
	if (lexer->cursor == '#')
		ignore_comment(lexer);
	
}
