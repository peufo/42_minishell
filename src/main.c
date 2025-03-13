/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:06 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/13 23:10:02 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	handle_signal(int sig)
{
	g_signal_received = sig;
}

void	actualise(t_sh *shell)
{
	shell->signal = g_signal_received;
}

int	main(int ac, char **av, char **env)
{
	t_sh		shell;
	t_string	file;

	shell_init(&shell, env);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	if (ac == 2)
	{
		file.value = NULL;
		string_push_str(&file, env_get(&shell, "PWD"));
		string_push_str(&file, "/");
		string_push_str(&file, av[1]);
		shell.pipe.in = open(file.value, O_RDONLY);
		string_free(&file);
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
