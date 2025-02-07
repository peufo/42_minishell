#include "minishell.h"

void	debug_new_tokens(t_sh *shell, char **toks)
{
	int	i;

	i = 0;
	while (toks[i] != NULL)
	{
		debug(shell, "new token is :");
		debug(shell, toks[i++]);
	}
}

void	debug_ast(t_sh *shell)
{
	(void)shell;
}