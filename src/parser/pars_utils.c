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

char    **parse_collector(char **toks, t_sh *shell)
{
    int     i;
    int     type;
    int     next_type;
    char    **ntoks;

    i = 0;
    while (toks[i] && toks[i + 1])
    {
        type = pars_get_type(toks[i]);
        next_type = pars_get_type(toks[i + 1]);
        while (type == AST_COMMAND && next_type == AST_COMMAND)
        {
            ntoks[shell->ast->log++] = ft_strjoin(toks[i], toks[i + 1]);
            free(toks[i]);
            free(toks[i + 1]);
            toks[i] = NULL;
            toks[i + 1] = NULL;
        }
        i++;
    }
    return (ntoks);
}

void	parse_handle_logical(t_sh *shell, t_ast *nodes, t_ast *ops)
{
	(void)shell;
	(void)nodes;
	(void)ops;
}

void	parse_handle_redirection(t_sh *shell, t_ast *nodes)
{
	(void)shell;
	(void)nodes;
}
