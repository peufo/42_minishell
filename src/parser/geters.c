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
        "|", "&&", "||", "<", "<<", ">>", ">", "(", ")", "abc", NULL
    };

    i = 0;
    if (tok == NULL)
        return (AST_END);
    while (find[i] != NULL && ft_strncmp(find[i], tok, ft_strlen(tok)))
        i++;
    if (i == 0)
        return (AST_PIPELINE);
    else if (i <= 2)
        return (AST_LOGICAL);
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


void	pars_end_check(t_sh *shell)
{
	if (!ft_strncmp(shell->lexer.tokens[0], "exitshell",
			ft_strlen(shell->lexer.tokens[0])))
		shell_exit(shell);
	shell->ast->args = shell->lexer.tokens;
}

int	check_for_simple_pars(t_sh *shell, char **toks)
{
	int	i;
	int	type;

	i = 0;
	while (toks[i] && 1)
	{
		type = pars_get_type(toks[i++]);
		if (type == AST_LOGICAL || type == AST_SUBSHELL)
			return (debug(shell, "ast ultime\n"), 0);
		else if (type != AST_COMMAND && type != AST_END)
			return (debug(shell, "ast++\n"), 2);
	}
	return (debug(shell, "simple AST\n"), 1);
}
