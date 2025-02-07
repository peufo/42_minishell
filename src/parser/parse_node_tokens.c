#include "minishell.h"

t_ast   *parse_node_command(char *token)
{
    t_ast	*node;

    printf("\n into node command \n ");
    node = NULL;
	node->type = AST_COMMAND;
    node->left = NULL;
    node->right = NULL;
    node->cmd = ft_strdup(token);
    return (node);
}

t_ast    *parse_node_operator(int type, t_ast *left, t_ast *right, int op)
{
    t_ast   *node;

    printf("\n into node operator \n ");
    node = NULL;
    node->type = type;
    node->left = left;
    node->right = right;
    node->op = op;
    node->cmd = NULL;
    return (node);
}

void    parse_node_subshell(t_sh *shell)
{
    (void)shell;
}
