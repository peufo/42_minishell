#include "minishell.h"

void	debug_new_tokens(t_sh *shell, char **toks)
{
	int	i;

	i = 0;
	while (toks[i] != NULL)
	{
		debug(shell, "\nnew token is :");
		debug(shell, toks[i++]);
	}
}

void	debug_ast(t_sh *shell)
{
	debug(shell, "///////////Welcome to the debug zone\\\\\\\\\\\\");
	debug(shell, "\n\n");
	shell_exit(shell);
}
