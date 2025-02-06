#include "minishell.h"

void    free_ast(t_ast *node)
{
    int i;

    if (!node)
        return ;
    i = 0;
    if (node->args)
    {
        while (node->args[i])
            free(node->args[i++]);
        free(node->args);
    }
    if (node->left)
        free_ast(node->left);
    if (node->right != NULL)
        free_ast(node->right);
    free(node);
}

static int  parse_toks_len(char **toks)
{
    int size;

    size = 0;
    while (toks[size])
        size++;
    return (size);
}

char    **parse_collector(char **toks)
{
    int     i;
    int     tsize;
    char    **args;

    i = 0;
    tsize = parse_toks_len(toks);
    args = malloc(tsize * sizeof(char *));
    if (!args)
        return (throw_error("Mallocs in :", __FILE__, __LINE__), NULL);
    while (*toks && !ft_isop(*toks) && ft_strncmp(*toks, ")",
            ft_strlen(*toks)))
    {
        args[i++] = *toks;
        toks++;
    }
    args[i] = NULL;
    return (args);
}

t_ast   parse_node_ast(t_atype type, t_aop op, t_ast *left, t_ast *right)
{
    t_ast   node;

    node.type = type;
    node.op = op;
    node.left = left;
    node.right = right;
    node.args = NULL;
    return (node);
}

t_ast   parse_redirection(char **toks)
{
    t_aop   op;
    t_ast   left;
    t_ast   right;

    op = AST_OP_NULL;
    left = parse_commands(toks);
    if (ft_strncmp(*toks, ">>", ft_strlen(*toks)))
        op = AST_OP_DGREAT;
    else if (ft_strncmp(*toks, ">", ft_strlen(*toks)))
        op = AST_OP_GREAT;
    else if (ft_strncmp(*toks, ">>", ft_strlen(*toks)))
        op = AST_OP_DLESS;
    else if (ft_strncmp(*toks, ">>", ft_strlen(*toks)))
        op = AST_OP_LESS;
    toks++;
    right = parse_commands(toks);
    return (parse_node_ast(AST_REDIRECT, op, &left, &right));
}