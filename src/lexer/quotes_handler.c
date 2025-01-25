#include "minishell.h"

static void	ignore_comment(t_lexer *lexer)
{
	while (lexer->cursor)
		lexer->cursor++;
}

static void	tokenise_single_quote(t_lexer *lexer)
{
	(void)lexer;
}

void	look_for_quotes(t_lexer *lexer)
{
	if (lexer->cursor == '#')
		ignore_comment(lexer);
	if (lexer->cursor == '\'')
		tokenise_single_quote(lexer);
	if (lexer->cursor == '"')
	{
		printf("handle doubnle quotes\n");
	}
}
