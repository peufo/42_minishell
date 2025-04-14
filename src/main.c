/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:06 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/14 12:05:29 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_is_sigint;

void	handle_signal_int(int sig)
{
	char	*prompt;
	char	*cursor;

	(void)sig;
	prompt = ft_strdup(rl_prompt);
	if (!prompt)
		return ;
	cursor = prompt;
	while (*cursor && *cursor != '\n')
		cursor++;
	*cursor = '\0';
	printf("\n%s\n", prompt);
	free(prompt);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_is_sigint = true;
}

int	main(int ac, char **av, char **env)
{
	t_sh	shell;

	shell_init(&shell, env);
	signal(SIGINT, handle_signal_int);
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
