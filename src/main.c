/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:06 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/18 07:30:49 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_sh	shell;

	shell_init(&shell, env);
	shell.debug_fd = open("./log/debug.log", O_RDWR | O_CREAT, 0666);
	if (ac == 2)
	{
		shell.pipe.in = open(av[1], O_RDONLY | O_NONBLOCK);
		if (shell.pipe.in == -1)
			return (shell_exit(&shell), 1);
		shell.name = av[1];
	}
	shell_exec(&shell);
	parse_free(&shell);
	return (0);
}
