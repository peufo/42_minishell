#include "minishell.h"

int check_gates(char **toks)
{
    int dif;

    dif = ft_strncmp(*toks, "&&", ft_strlen(*toks));
    if (dif == 0)
        return (0);
    dif = ft_strncmp(*toks, "||", ft_strlen(*toks));
    if (dif == 0)
        return (0);
    return (1);
}

int pars_get_type(char *tok)
{
    int         i;
    static char *find[] = {
        "&&", "||", "|", "<", "<<", ">>", ">", "(", ")", "abc", NULL
    };

    i = 0;
    if (tok == NULL)
        return (AST_END);
    while (find[i] != NULL && ft_strncmp(find[i], tok, ft_strlen(tok)))
        i++;
    if (i <= 1)
        return (AST_LOGICAL);
    else if (i == 2)
        return (AST_PIPELINE);
    else if (i <= 5)
        return (AST_REDIRECT);
    else if (i <= 7)
        return (AST_SUBSHELL);
    else
        return (AST_COMMAND);
}

int  parse_toks_len(char **toks)
{
    int size;

    size = 0;
    while (toks[size])
        size++;
    return (size);
}
