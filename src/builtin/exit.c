/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:13:34 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/14 22:58:34 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_ast *node)
{
	if (node->shell->is_interactive)
		ft_putstr("exit\n");
	shell_exit(node->shell);
	return (0);
}
