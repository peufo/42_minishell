#include "minishell.h"

t_ast   *parse_node_command(char *token)
{
    t_ast	*node;

	node->type = AST_COMMAND;
    node->left = NULL;
    node->right = NULL;
    node->cmd = ft_strdup(token);
    return (node);
}

void    parse_node_operator(t_sh *shell, t_nstack *nodes, t_nstack *ops)
{
    debug(shell, "Entering node logical \n");
    (void)nodes;
    (void)ops;
}

void    parse_node_subshell(t_sh *shell)
{
    (void)shell;
}
