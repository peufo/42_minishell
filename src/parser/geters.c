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
        "&&",
        "||",
        "|",
        "<",
        "<<",
        ">>",
        ">",
        "abc",
        "efg"
    };

    i = 0;
    if (tok == NULL)
        return (AST_END);
    while (ft_strncmp(find[i], tok, ft_strlen(tok)) && i < 6)
        i++;
    if (i <= 1)
        return (AST_LOGICAL);
    else if (i == 2)
        return (AST_PIPELINE);
    else if (i <= 5)
        return (AST_REDIRECT);
    else
        return (AST_COMMAND);
}

static void debug_right_part(t_sh *shell, t_ast *node)
{
    return ;
    if (node->left)
    {
        debug(shell, "[RIGHT SUBTREE]\n");
        debug_node(shell, node);
    }
    (void)node;
}

static void debug_left_part(t_sh *shell, t_ast *node)
{
    return ;
    if (node->left)
    {
        debug(shell, "[LEFT SUBTREE]\n");
        debug_node(shell, node);
    }
    (void)node;
}

void    debug_node(t_sh *shell, t_ast *node)
{
    int i;

    i = 0;
    debug(shell, "NEW NODE\n");
    debug(shell, "TYPE IS :\n");
    if (node->type == AST_COMMAND)
    {
        debug(shell, "[Command]\n");
        while (node->args && node->args[i] != NULL)
           debug(shell, node->args[i++]);
        debug(shell, "\n");
    }
    else if (node->type == AST_PIPELINE)
        debug(shell, "[Pipe node]\n");
    else if (node->type == AST_LOGICAL)
    {
        debug(shell, "[Logical]\n");
        if (node->op == AST_OP_OR)
            debug(shell, "[AND]\n");
        else
            debug(shell, "[OR]\n");
    }
    debug_left_part(shell, node);
    debug_right_part(shell, node);
    debug(shell, "\n\n");
}
