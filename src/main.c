/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:06 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/11 10:47:31 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	handle_signal(int sig)
{
	g_signal_received = sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	actualise(t_sh *shell)
{
	shell->signal = g_signal_received;
}

int	main(int ac, char **av, char **env)
{
	t_sh	shell;

	shell_init(&shell, env);
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
	if (ac == 2)
	{
		shell.pipe.in = open(av[1], O_RDONLY | O_NONBLOCK);
		if (shell.pipe.in == -1)
			return (shell_exit(&shell), 1);
		shell.name = av[1];
	}
	shell_exec(&shell);
	ast_free(&shell.ast);
	return (0);
}

int	debug_get_fd(void)
{
	static int	debug_fd = -1;

	if (debug_fd == -1)
		debug_fd = open("./log/debug.log", O_RDWR | O_CREAT | O_TRUNC, 0666);
	return (debug_fd);
}
