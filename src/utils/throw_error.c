/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:06:10 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/14 12:59:52 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	throw_error2(t_sh *shell, char **error)
{
	ft_putstr_fd(shell->name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	while (*error)
		ft_putstr_fd(*(error++), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	shell->exit_status = 1;
	return (1);
}

int	throw_error(t_ast *node, char **error)
{
	ft_putstr_fd(node->shell->name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	while (*error)
		ft_putstr_fd(*(error++), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	node->status = 1;
	node->shell->exit_status = 1;
	return (1);
}
