#include "minishell.h"

void	parse_free(t_sh *shell)
{
	debug(shell, "Freeing AST ???\n");
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

    i = 0;
    if (n == 2)
        return (ft_strjoin(toks[start], toks[start + 1]));
    else
    {
        len = 0;
        while (toks[start + i])
            len +=  ft_strlen(toks[start + i++]) + 1;
        a = malloc(len * sizeof(char) + 1);
        if (!a)
            return (throw_error("malloc in : ", __FILE__, __LINE__), NULL);
        i = 0;
        ft_memset(a, 0, len + 1);
        while (i < n - 1)
        {
            ft_strlcat(a, toks[start + i++], len);
            if (i < n - 1)
                ft_strlcat(a, " ", len);
        }
    }
    return (a);
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
    ntoks = malloc(parse_toks_len(toks) * sizeof(char *));
    types = malloc(parse_toks_len(toks) * sizeof(int));
    if (!types)
        return (throw_error("malloc in :", __FILE__, __LINE__), NULL);
    while (i < parse_toks_len(toks))
        types[i++] = 0;
    i = 0;
    while (toks[i] != NULL)
    {
        k = 0;
        types[k++] = pars_get_type(toks[i++]);
        while (toks[i] != NULL && types[k - 1] == AST_COMMAND)
            types[k++] = pars_get_type(toks[i++]);
        if (k >= 2)
            ntoks[j++] = assemble(toks, k, i - k);
        else if (toks[i] != NULL)
            ntoks[j++] = ft_strdup(toks[i - k]);
    }
    ntoks[j] = NULL;
    free(types);
    return (ntoks);
}
