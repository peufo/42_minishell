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

int  parse_toks_len(char **toks)
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
