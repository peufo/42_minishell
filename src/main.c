/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:06 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/03 20:57:15 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_is_sigint;

void	handle_signal(int sig)
{
	static const char	eot = '\004';

	if (sig == SIGINT)
		g_is_sigint = true;
	ioctl(STDIN_FILENO, TIOCSTI,  &eot);
}

int	main(int ac, char **av, char **env)
{
	t_sh	shell;

	shell_init(&shell, env);
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
