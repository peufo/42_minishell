#include "minishell.h"

void	push_node(t_sh *shell, t_nstack **nodes, t_ast *node)
{
	t_nstack	*new;

	new = malloc(sizeof(t_nstack));
	if (!new)
		return (throw_error("malloc in :", __FILE__, __LINE__));
	new->ast = node;
	new->next = *nodes;
	*nodes = new;
}

t_ast	*extract_node(t_sh *shell, t_nstack **nodes)
{
	t_ast		*node;
	t_nstack	*head;

	if (*nodes)
		return (NULL);
	debug(shell, "\n extracting top node \n");
	head = *nodes;
	node = head->ast;
	*nodes = head->next;
	free(head);
	return (node);
}

static void	parse_handle_gates(t_sh *shell, t_nstack *nodes, t_nstack *ops, int operator)
{
	(void)shell;
	(void)nodes;
	(void)ops;
	(void)operator;
}

void	parse_handle_logical(t_sh *shell, t_nstack *nodes, t_nstack *ops, int type)
{
	int		operator;
	t_ast	*op_node;

	op_node = NULL;
	operator = pars_declare_operator(ops)->op;
	if (type == AST_LOGICAL)
		return (parse_handle_gates(shell, nodes, ops, operator));
	while (ops && operator == AST_PIPELINE)
	{
		op_node = extract_node(shell, &ops);
		op_node->right = extract_node(shell, &nodes);
		op_node->left = extract_node(shell, &nodes);
		push_node(shell, &nodes, op_node);
		operator = pars_declare_operator(ops)->op;
	}
	push_node(shell, &ops, parse_node_operator(shell, NULL, NULL, operator));
}

void	parse_handle_redirection(t_sh *shell, t_nstack *nodes, t_nstack *ops)
{
	(void)shell;
	(void)nodes;
	(void)ops;
}
