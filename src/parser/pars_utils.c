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

    printf("n == %d\n", n);
    if (n == 1)
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
    printf("tokens in collector : %s", toks[i]);
    ntoks = malloc(parse_toks_len(toks) * sizeof(char *));
    types = malloc(parse_toks_len(toks) * sizeof(int));
    if (!types)
        return (throw_error("malloc in :", __FILE__, __LINE__), NULL);
    while (i < parse_toks_len(toks))
        types[i++] = 0;
    i = 0;
    types[0] = pars_get_type(toks[0]);
    printf("first type is : %d \n", types[0]);
    while (toks[i])
    {
        k = 0;
        printf("newloop\n");
        while (types[k] == AST_COMMAND)
            types[k++] = pars_get_type(toks[i++]);
        printf("last type is : %d \n", types[k]);
        if (types[0] == 0)
            return (free(ntoks), free(types), NULL);
        else if (k >= 1)
        {
            printf("it will assemble\n");
            ntoks[j++] = assemble(toks, k, i++ - k);
        }
        else
            ntoks[j++] = ft_strdup(toks[i++]);
    }
    printf("out of the loop\n");
    free(types);
    printf("\n %s\n", ntoks[0]);
    return (ntoks);
}
