#include "minishell.h"

// ----==== CHECK IF NB PARENTHESIS IS OK ====---- //

int		check_parenthesis(t_sh *shell)
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

int		check_gate_following(t_sh *shell)
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

int		check_pipe_following(t_sh *shell)
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

int		check_pipe_following(t_sh *shell)
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