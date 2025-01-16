/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:06 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/16 01:04:23 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	t_sh	shell;

	shell_init(&shell);
	if (ac == 2)
	{
		shell.pipe.in = open(av[1], O_RDONLY | O_NONBLOCK);
		if (shell.pipe.in == -1)
			shell_exit(&shell);
		shell.name = av[1];
	}
	shell_exec(&shell);
	return (0);
}
