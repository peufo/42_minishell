/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:22:31 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/23 16:21:40 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * builtin is executed on main process
 */
int	exec_command(t_ast *node)
{
	t_exe	builtin;

	builtin = get_builtin(*node->tokens);
	if (builtin)
		return (builtin(node));
	exec_child(node, exec_bin);
	waitpid(node->pid, &node->status, 0);
	return (node->status);
}
