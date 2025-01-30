/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:43:54 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 16:01:18 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug(t_sh *shell, char *str)
{
	ft_putstr_fd(str, shell->debug_fd);
}

void	debug_arr(t_sh *shell, char **arr)
{
	while (*arr)
	{
		debug(shell, *arr);
		arr++;
	}
}
