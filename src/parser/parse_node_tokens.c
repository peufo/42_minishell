#include "minishell.h"

t_ast   *parse_node_command(char *token)
{
    t_ast	*node;

    printf("\n into node command \n ");
    node = malloc(sizeof(t_ast));
    if (!node)
    {
        return (throw_error("malloc in:", __FILE__, __LINE__), NULL);
    }
	node->type = AST_COMMAND;
    node->left = NULL;
    node->right = NULL;
    if (token)
        node->cmd = ft_strdup(token);
    printf("\n outside node command \n");
    return (node);
}

t_ast    *parse_node_operator(int type, t_ast *left, t_ast *right, int op)
{
    t_ast   *node;

    printf("\n into node operator \n ");
    node = malloc(sizeof(t_ast));
    if (!node)
        return (throw_error("malloc in:", __FILE__, __LINE__), NULL);
    node->type = type;
    node->left = left;
    node->right = right;
    node->op = op;
    node->cmd = NULL;
    printf("\n outside node operator \n");
    return (node);
}

void    parse_node_subshell(t_sh *shell)
{
    (void)shell;
}
