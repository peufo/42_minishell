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

void    parse_node_operator(int type, t_ast *left, t_ast *right, int op)
{
    (void)type;
    (void)left;
    (void)right;
    (void)op;
}

void    parse_node_subshell(t_sh *shell)
{
    (void)shell;
}
