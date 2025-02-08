#include "minishell.h"

static char	**parse_word_content(void *element)
{
	t_utils	*u;
	char	**cmd;
	char	*str;

	u->i = 0;
	u->j = 0;
	u->k = 0;
	u->x = 0;
	str = (char *)element;
	while (str[u->i])
	{
		/*
			cmd	-> args -> var ?
			dup the line
							*/
	}
}

static void	parse_node_subscript(t_nstack **tmp, t_list *ops, t_list *cms, int ocount)
{
	while (ocount > 0 && ops != NULL)
	{
		(*tmp)->ast->left->args = parse_word_content(cms->content);
		cms = cms->next;
		(*tmp)->ast->right->args = parse_word_content(cms->content);
		(*tmp)->ast->args = NULL;
		(*tmp)->ast->type = pars_get_type((char *)ops->content);
		(*tmp)->ast->op = ft_strdup((char *)ops->content);
		ops = ops->next;
		*tmp = (*tmp)->next;
		ocount--;
	}
}

t_ast	*parse_handle_subscript(char **toks, int len, t_sh *shell)
{
	t_nstack	*tmp;
	t_list		*ops;
	t_list		*cms;
	int			nb_ops;

	nb_ops = 0;
	tmp = malloc(sizeof(t_nstack));
	ops = pars_get_typelist(toks, AST_LOGICAL, shell);
	cms = pars_get_typelist(toks, AST_COMMAND, shell);
	while (len > 0)
		if (toks[--len] != AST_COMMAND)
			nb_ops++;
	parse_node_subscript(shell, &tmp, ops, nb_ops);
	ft_lstclear(ops, free);
	ft_lstclear(cms, free);
	return (tmp->ast);
}
