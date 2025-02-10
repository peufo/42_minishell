/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:10:16 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/10 15:53:44 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**parse_word_content(char *element)
{
	t_utils	u;
	char	**cmd;

	cmd = malloc(3 * sizeof(char *));
	if (!cmd)
		return (throw_error("malloc in :", __FILE__, __LINE__), NULL);
	ft_bzero(&u, sizeof(u));
	while (ft_isalnum(element[u.i]))
		u.i++;
	cmd[0] = malloc(u.i + 1);
	cmd[0] = ft_substr(element, 0, u.i);
	if (ft_isspace(element[u.i]))
		u.i++;
	while (element[u.i + u.j])
		u.j++;
	cmd[1] = malloc(1 + u.j++);
	cmd[1] = ft_substr(element, u.i, u.i + u.j);
	cmd[2] = NULL;
	return (cmd);
}

static t_ast	*parse_node_operator(
	t_nstack *tmp,
	t_list *ops,
	t_list *cms,
	int *ocount)
{
	char	*str;
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	node->left = pars_init_ast();
	node->right = pars_init_ast();
	if (!cms || *ocount == 0)
		return (NULL);
	str = (char *)cms->content;
	if (!tmp->ast->left)
		node->left->args = parse_word_content(str);
	else
		node->left = tmp->ast;
	cms = cms->next;
	node->right->args = parse_word_content(cms->content);
	node->args = NULL;
	node->op = (t_aop)((char *)ops->content);
	if (ops)
		ops = ops->next;
	(*ocount)--;
	return (node);
}

t_ast	*parse_handle_subscript(char **toks, int len, t_sh *shell)
{
	t_nstack	*tmp;
	t_list		*ops;
	t_list		*cms;
	int			nb_ops;

	nb_ops = 0;
	tmp = malloc(sizeof(t_nstack));
	if (!tmp)
		return (throw_error("malloc in :", __FILE__, __LINE__), NULL);
	ops = pars_get_typelist(toks, AST_LOGICAL, shell);
	cms = pars_get_typelist(toks, AST_COMMAND, shell);
	nb_ops = parse_get_nbops(toks, len);
	debug_arr(shell, (char *[]){"ops : ", ft_itoa(nb_ops), "\n", NULL});
	while (nb_ops != 0)
	{
		debug(shell, "looping\n");
		tmp->ast = pars_init_ast();
		tmp->ast->op = AST_OP_NULL;
		tmp->ast->type = pars_get_type((char *)ops->content);
		tmp->ast->left = parse_node_operator(tmp, ops, cms, &nb_ops);
		tmp->ast->right = parse_node_operator(tmp, ops, cms, &nb_ops);
		tmp = tmp->next;
	}
	ft_lstclear(&ops, free);
	ft_lstclear(&cms, free);
	return (tmp->ast);
}
