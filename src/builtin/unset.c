/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:38:02 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/21 14:41:35 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_sh *shell, t_command *cmd)
{
	(void)cmd;
	ft_putstr_fd("TODO\n", shell->pipe.out);
	return (0);
}
