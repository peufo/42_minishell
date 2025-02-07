#include "minishell.h"

void	parse_push_node(t_sh *shell, t_nstack **tmp, t_ast *node)
{
	t_nstack	*new;

	debug(shell, "pushing node \n");
	new = malloc(sizeof(t_nstack));
	if (!new)
		return (throw_error("malloc in :", __FILE__, __LINE__));
	new->ast = node;
	new->next = *tmp;
	*tmp = new;
}

t_ast	*parse_extract_node(t_sh *shell, t_nstack **tmp)
{
	t_ast		*node;
	t_nstack	*head;

	if (*tmp)
		return (NULL);
	debug(shell, "\n extracting top node \n");
	head = *tmp;
	node = head->ast;
	*tmp = head->next;
	free(head);
	return (node);
}

static void	parse_handle_gates(t_sh *shell, t_nstack *tmp,
		t_nstack *ops, int operator)
{
	(void)shell;
	(void)tmp;
	(void)ops;
	(void)operator;
}

void	parse_handle_logical(t_sh *shell, t_nstack *tmp,
		t_nstack *ops, int type)
{
	int		operator;
	t_ast	*op_node;

	op_node = NULL;
	operator = pars_declare_operator(ops)->op;
	if (type == AST_LOGICAL)
		return (parse_handle_gates(shell, tmp, ops, operator));
	while (ops && operator == AST_PIPELINE)
	{
		op_node = parse_extract_node(shell, &ops);
		op_node->right = parse_extract_node(shell, &tmp);
		op_node->left = parse_extract_node(shell, &tmp);
		parse_push_node(shell, &tmp, op_node);
		operator = pars_declare_operator(ops)->op;
	}
	parse_push_node(shell, &ops,
		parse_node_operator(AST_PIPELINE, NULL, NULL, operator));
}

void	parse_handle_redirection(t_sh *shell, t_nstack *tmp, char **tokens)
{
	int		type;
	t_ast	*left;
	t_ast	*right;
	t_ast	*direction;

	left = parse_extract_node(shell, &tmp);
	right = parse_node_command(tokens[1]);
	type = pars_get_type(tokens[0]);
	direction = parse_node_operator(AST_REDIRECT, left, right, type);
	parse_push_node(shell, &tmp, direction);
}
