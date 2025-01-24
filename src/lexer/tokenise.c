#include "minishell.h"
#include "macros.h"

void 	tokenise_quotes(t_sh *shell)
{
	(void)shell;
}

void 	tokenise_gates(shell)
{
	t_token		*token;

	token = malloc(sizeof(t_string));
	if (!token)
	{
		message(MALLOC_ERROR);
		return ;
	}
	if (*shell->lexer.cursor == '&')
	{
		token->tyoe
	}
}