/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:21:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/14 14:37:54 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_exit(t_sh *shell, char *error)
{
	(void)shell;
	if (!error)
		return (0);
	perror(error);
	return (1);
}

void	shell_init(t_sh *shell, t_pipe p)
{
	shell->pipe = p;
	shell->is_interactive = isatty(p.in);
}
