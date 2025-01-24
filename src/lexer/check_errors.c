#include "minishell.h"

// ----==== CHECK IF NB PARENTHESIS IS OK ====---- //

static int		check_parenthesis(t_sh *shell)
{
	int		i;

	i = 0;
	while (shell->lexer.cursor[i])
	{
		while (1)
		{
			(void)shell;
			return (KO);
		}
	}
	return (OK);
}

// ----==== CHECK IF GATE HAS SOMETHING ====---- //

static int		check_gate_following(t_sh *shell)
{
	int		i;

	i = 0;
	while (shell->lexer.cursor[i])
	{
		while (1)
		{
			(void)shell;
			return (KO);
		}
	}
	return (OK);
}

// ----==== CHECK IF PIPE HAS SOMETHING ====---- //

static int		check_pipe_following(t_sh *shell)
{
	int		i;

	i = 0;
	while (shell->lexer.cursor[i])
	{
		while (1)
		{
			(void)shell;
			return (KO);
		}
	}
	return (OK);
}

// ----==== CHECK IF REDIRECTION HAS SOMETHING ====---- //

static int		check_redir_following(t_sh *shell)
{
	int		i;

	i = 0;
	while (shell->lexer.cursor[i])
	{
		while (1)
		{
			(void)shell;
			return (KO);
		}
	}
	return (OK);
}

int 	check_errors(t_sh *shell, char c)
{
	(void)shell;
	(void)c;
	return (OK);
}