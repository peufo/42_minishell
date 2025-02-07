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

void    parse_node_pipeline(t_sh *shell, t_nstack *nodes, t_nstack *ops)
{
    t_ast   *node;

    debug(shell, "Entering node pipe \n");
    node = NULL;
    (void)node;
}

void    parse_node_logical(t_sh *shell, t_nstack *nodes, t_nstack *ops)
{
    debug(shell, "Entering node logical \n");
    (void)nodes;
    (void)ops;
}

void    parse_node_redirection(t_sh *shell, t_nstack *nodes, t_nstack *ops)
{
    debug(shell, "Into node redirection \n");
    (void)nodes;
    (void)ops;
}
