#include "minishell.h"

static void	parse_node_operators(t_nstack **tmp, t_list *ops, t_list *cms, int nb_ops)
{
	if (nb_ops)
}

t_ast	*parse_handle_subscript(char **toks, int len, t_sh *shell)
{
	t_nstack	*tmp;
	t_list		*ops;
	t_list		*cms;
	int			nb_ops;

	tmp = NULL;
	nb_ops = 0;
	ops = pars_get_typelist(toks, AST_LOGICAL, shell);
	cms = pars_get_typelist(toks, AST_COMMAND, shell);
	while (len > 0)
		if (toks[--len] != AST_COMMAND)
			nb_ops++;
	parse_node_operators(shell, &tmp, ops, nb_ops);
	return (tmp->ast);
}
