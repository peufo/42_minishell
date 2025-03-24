/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:06 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/24 10:33:04 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_signal;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
		g_signal.is_sigint = true;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	actualise(t_sh *shell)
{
	(void)shell;
}

int	main(int ac, char **av, char **env)
{
	t_sh	shell;

	shell_init(&shell, env);
	ft_bzero(&g_signal, sizeof(t_signal));
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
	if (ac == 2)
	{
		shell.pipe.in = open(av[1], O_RDONLY);
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
