/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:06 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/29 17:09:57 by jvoisard         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	t_sh	shell;

	shell_init(&shell, env);
	ft_bzero(&g_signal, sizeof(t_signal));
	signal(SIGINT, &handle_signal);
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
