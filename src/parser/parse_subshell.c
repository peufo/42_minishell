/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:10:16 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/11 07:57:29 by dyodlm           ###   ########.fr       */
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
	cmd[0] = ft_substr(element, 0, u.i);
	if (ft_isspace(element[u.i]))
		u.i++;
	while (element[u.i + u.j])
		u.j++;
	cmd[1] = ft_substr(element, u.i, u.i + u.j);
	cmd[2] = NULL;
	return (cmd);
}

static t_ast	*parse_node_context(char *tok)
{
	t_ast	*node;

	node = pars_init_ast();
	if (!node)
		return (NULL);
	node->args = parse_word_content(tok);
	node->type =pars_get_type(tok);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static void	parse_node_op(t_ast **c_node, t_list **ops, t_nstack **stack)
{
	t_ast	*o_node;

	o_node = pars_init_ast();
	if (!o_node)
		return (throw_error("malloc :", __FILE__, __LINE__));
	o_node->op = pars_get_op((char *)(*ops)->content);
	o_node->type = pars_get_type((char *)(*ops)->content);
	o_node->left = (*stack)->ast;
	o_node->right = *c_node;
	(*stack)->ast = o_node;
	*ops = (*ops)->next;
}

static t_nstack	*init_stack(void)
{
	t_nstack	*s;

	s = malloc(sizeof(t_nstack));
	s->ast = pars_init_ast();
	s->previous = NULL;
	s->next = NULL;
	return (s);
}

static void	print_ast(t_ast *node, int depth)
{
	int	i;

	i = 0;
	if (!node)
		return;
	while (i++ < depth)
		printf("  ");
	if (node->type == AST_LOGICAL)
		printf("Operator: %d\n", node->op);
	else
	{
		i = 0;
		printf("Command: ");
		while (node->args && node->args[i])
			printf("%s ", node->args[i++]);
		printf("\n");
	}

	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}

static void print_nstack(t_nstack *stack)
{
	if (!stack)
		return;
	printf("AST Structure:\n");
	print_ast(stack->ast, 0);
}

static void	parse_free_stack(t_nstack *stack)
{
	(void)stack;
}

t_nstack	*parse_handle_subscript(char **toks, t_sh *shell)
{
	t_nstack	*stack;
	t_ast		*c_node;
	t_list		*ops;
	t_list		*cms;

	stack = init_stack();
	ops = pars_get_typelist(toks, AST_LOGICAL, shell);
	cms = pars_get_typelist(toks, AST_COMMAND, shell);
	while (cms)
	{
		c_node = parse_node_context((char *)cms->content);
		if (ops)
			parse_node_op(&c_node, &ops, &stack);
		else
			stack->ast = c_node;
		cms = cms->next;
	}
	ft_lstclear(&ops, free);
	ft_lstclear(&cms, free);
	print_nstack(stack);
	parse_free_stack(stack);
	shell_exit(shell);
	return (stack);
}
