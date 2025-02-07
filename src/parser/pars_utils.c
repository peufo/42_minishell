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

t_ast   *pars_declare_operator(t_nstack *ops)
{
    if (ops)
        return (ops->ast);
    return (NULL);
}

int  parse_toks_len(char **toks)
{
    int size;

    size = 0;
    while (toks[size])
        size++;
    return (size);
}

static char *assemble(char **toks, int n, int start)
{
    int     len;
    int     i;
    char    *a;

    if (n == 2)
        return (ft_strjoin(toks[start], toks[start + 1]));
    else
    {
        len = 0;
        while (toks[start + i])
            len +=  ft_strlen(toks[start + i++]);
        a = malloc(len * sizeof(char));
        if (!a)
            return (throw_error("malloc in : ", __FILE__, __LINE__), NULL);
        i = 0;
        while (i < n)
            ft_strlcat(a, toks[start + i++], len);
    }
    return (NULL);
}

char    **parse_collector(char **toks)
{
    int     i;
    int     j;
    int     k;
    int     *types;
    char    **ntoks;

    i = 0;
    j = 0;
    ntoks = NULL;
    types = malloc(parse_toks_len(toks) * sizeof(int));
    if (!types)
        return (throw_error("malloc in :", __FILE__, __LINE__), NULL);
    while (toks[i])
    {
        k = 0;
        while (types[k] == AST_COMMAND)
            types[k++] = pars_get_type(toks[i++]);
        ntoks[j++] = assemble(toks, k, i - k);
    }
    free(types);
    return (ntoks);
}
