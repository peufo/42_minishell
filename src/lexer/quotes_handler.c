#include "minishell.h"

static void	ignore_comment(t_lexer *lexer)
{
	while (lexer->cursor)
		lexer->cursor++;
}

static void	tokenise_single_quote(t_lexer *lexer)
{
	t_list	*start;

	start = lexer->starters;
	lexer_add_token(lexer, L_WORD, ft_substr(start, 0, lexer->cursor - start));
}

static void	tokenise_double_quote(t_lexer *lexer)
{
	(void)lexer;
}

void	look_for_quotes(t_lexer *lexer)
{
	char	*start;

	start = lexer->cursor;
	if (lexer->cursor == '#')
		ignore_comment(lexer);
	else if (lexer->cursor == '\'')
		Q1(lexer);
	else if (lexer->cursor == '"')
		D1(lexer);
//	lexer_add_token(lexer, L_WORD, ft_substr(start, 0, lexer->cursor - start));
}
