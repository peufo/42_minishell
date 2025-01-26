#include "minishell.h"

void	tokenise_single_quote(t_lexer *lexer)
{
	t_list	*start;

	start = ft_lstlast(lexer->starters);
	lexer_add_token(lexer, L_WORD, ft_substr(start, 0, lexer->cursor - start));
	ft_lstdelone(start, free);
}

void	tokenise_double_quote(t_lexer *lexer)
{
	t_list	*start;

	start = ft_lstlast(lexer->starters);
	lexer_add_token(lexer, L_WORD, ft_substr(start, 0, lexer->cursor - start));
	ft_lstdelone(start, free);
}

void	tokenise_variable(t_lexer *lexer)
{
	(void)lexer;
}