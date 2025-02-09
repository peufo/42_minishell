#include "minishell.h"

static char	**parse_word_content(void *element)
{
	t_utils	*u;
	char	**cmd;
	char	*str;

	u = NULL;
	cmd = NULL;
	init_utils(&u);
	str = (char *)element;
	while (str[u->i])
	{
		while (ft_isalnum(str[u->i]))
			u->i++;
		cmd[u->k] = malloc(u->i + 1);
		if (!cmd[u->k])
			return (free_2dtab(cmd), NULL);
		while (ft_isalnum(str[u->x]))
			cmd[u->k][u->j++] = str[u->x++];
		cmd[u->k][u->j] = '\0';
		if (ft_isspace(str[u->i]))
			u->i++;
		u->k++;
	}
	cmd[u->k] = NULL;
	free(u);
	return (cmd);
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
		(*tmp)->ast->op = (t_aop)((char *)ops->content);
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
	printf("hello\n");
	tmp = malloc(sizeof(t_nstack));
	ops = pars_get_typelist(toks, AST_LOGICAL, shell);
	cms = pars_get_typelist(toks, AST_COMMAND, shell);
	while (len > 0)
		if (pars_get_type(toks[--len]) != AST_COMMAND)
			nb_ops++;
	parse_node_subscript(&tmp, ops, cms, nb_ops);
	ft_lstclear(&ops, free);
	ft_lstclear(&cms, free);
	return (tmp->ast);
}
