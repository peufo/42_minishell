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
	debug(shell, "/////////// Welcome to the debug zone\\\\\\\\\\\\");
	debug(shell, "\n\n");
	debug_node(shell, shell->ast, 0);
	shell_exit(shell);
}

void	debug_two_lists(t_sh *shell, t_list *l1, t_list *l2)
{
	t_list	*lst;

	if (!l1 && !l2)
		return ;
	if (l1)
		lst = l1;
	else
		lst = l2;
	while (lst != NULL)
	{
		debug(shell, "\nelement :");
		debug(shell, (char *)lst->content);
		lst = lst->next;
	}
	debug(shell, "\n");
	if (l1)
	{
		lst = l2;
		debug_two_lists(shell, NULL, lst);
	}
	debug(shell, "end of debug list\n");
}
