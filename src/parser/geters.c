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

static void debug_right_part(t_sh *shell, t_ast *node)
{
    (void)shell;
    (void)node;
}

static void debug_left_part(t_sh *shell, t_ast *node)
{
    (void)shell;
    (void)node;
}

void    debug_node(t_sh *shell, t_ast *node)
{
    return ;
    debug(shell, "NEW NODE\n");
    debug(shell, "TYPE IS :\n");
    debug_arr(shell, (char **)(
        ft_itoa(node->type),
        "\nOPERATOR IS :",
        ft_itoa(node->op),
        "\nTO THE LEFT IS:",
        NULL
    ));
    debug_left_part(shell, node);
    debug_right_part(shell, node);
    debug(shell, "\n");
}
