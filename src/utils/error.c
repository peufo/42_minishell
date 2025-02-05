/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:20:31 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/05 14:37:54 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	throw_error(char *error, char *file, int line)
{
	ft_putstr_fd("\n\n", STDERR_FILENO);
	ft_putstr_fd("\033[31m", STDERR_FILENO);
	ft_putstr_fd("ERROR:\t", STDERR_FILENO);
	ft_putstr_fd("\033[0m", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(":", STDERR_FILENO);
	ft_putstr_fd(ft_itoa(line), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n\n", STDERR_FILENO);
}
