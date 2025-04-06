/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:06:10 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/06 12:46:27 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	throw(t_ast *node, char **error)
{
	if (error)
	{
		ft_putstr_fd(node->shell->name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		while (*error)
			ft_putstr_fd(*(error++), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
	{
		perror(node->shell->name);
	}
	errno = false;
	if (!node->status)
		node->status = 1;
	node->shell->exit_status = node->status;
	if (node->is_child_process && !node->is_herdoc)
		shell_exit(node->shell);
	return (node->status);
}
