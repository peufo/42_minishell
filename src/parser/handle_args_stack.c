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

void	get_top_type(t_sh *shell, t_nstack **nodes)
{
	(void)shell;
	(void)nodes;
}

void	parse_handle_logical(t_sh *shell, t_nstack *nodes, t_nstack *ops)
{
	(void)shell;
	(void)nodes;
	(void)ops;
}

void	parse_handle_redirection(t_sh *shell, t_nstack *nodes, t_nstack *ops)
{
	(void)shell;
	(void)nodes;
}
