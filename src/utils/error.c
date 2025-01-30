/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:20:31 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 15:31:27 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	throw_error(char *error, char *file, int line)
{
	ft_putstr_fd("\n\n", 1);
	ft_putstr_fd("\033[31m", 1);
	ft_putstr_fd("ERROR:\t", 1);
	ft_putstr_fd("\033[0m", 1);
	ft_putstr_fd(file, 1);
	ft_putstr_fd(":", 1);
	ft_putstr_fd(ft_itoa(line), 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(error, 1);
	ft_putstr_fd("\n\n", 1);
}
