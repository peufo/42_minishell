#include "minishell.h"

int	pars_get_type(char *tok)
{
	int			i;
	static char	*find[] = {
		"|", "&&", "||", "<", "<<", ">>", ">", "(", ")", "abc", NULL
	};

	i = 0;
	if (tok == NULL)
		return (AST_END);
	while (find[i] != NULL && ft_strncmp(find[i], tok, ft_strlen(tok)))
		i++;
	if (i == 0)
		return (AST_PIPELINE);
	else if (i <= 2)
		return (AST_LOGICAL);
	else if (i <= 5)
		return (AST_REDIRECT);
	else if (i <= 7)
		return (AST_SUBSHELL);
	else
		return (AST_COMMAND);
}

int	parse_toks_len(char **toks)
{
	int	size;

	size = 0;
	while (toks[size])
		size++;
	return (size);
}

int	parse_get_nbops(char **toks, int len)
{
	int	n;

	n = 0;
	while (len > 0)
		if (pars_get_type(toks[--len]) != AST_COMMAND)
			n++;
	return (n);
}

t_list	*pars_get_typelist(char **toks, int mod, t_sh *shell)
{
	t_list	*lst;
	int		type;
	int		i;

	i = 0;
	lst = NULL;
	type = pars_get_type(toks[i]);
	while (toks[i] && type != AST_END)
	{
		if (mod == AST_COMMAND)
		{
			if (type == mod)
				ft_lstadd_back(&lst, ft_lstnew(toks[i]));
		}
		else
		{
			if (type != AST_COMMAND)
				ft_lstadd_back(&lst, ft_lstnew(toks[i]));
		}
		type = pars_get_type(toks[++i]);
	}
	debug_two_lists(shell, NULL, lst);
	return (lst);
}
