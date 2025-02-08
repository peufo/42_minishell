#include "minishell.h"

t_ast	*parse_handle_subscript(char **toks, int len, t_sh *shell)
{
	int			i;
	t_nstack	*ops;
	t_nstack	*cms;
	t_nstack	*tmp;

	i = 0;
	tmp = NULL;
	ops = pars_get_ops(toks);
	cms = pars_get_cms(toks);
	while (i < len)
	{
		//	commands
		//	ops
		i++;
	}
}