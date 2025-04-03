/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:06 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/03 18:52:35 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_is_sigint;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
		g_is_sigint = true;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int ac, char **av, char **env)
{
	t_sh	shell;

	shell_init(&shell, env);
	g_is_sigint = false;
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
	if (ac == 2)
	{
		shell.fd_in = open(av[1], O_RDONLY);
		if (shell.fd_in == -1)
			return (shell_exit(&shell), 1);
		shell.name = av[1];
	}
	shell_exec(&shell);
	shell_exit(&shell);
	return (0);
}
