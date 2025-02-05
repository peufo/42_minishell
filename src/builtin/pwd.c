/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:33:56 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/05 01:31:55 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_sh *shell)
{
	ft_putstr_fd(shell->cwd, shell->pipe.out);
	ft_putstr_fd("\n", shell->pipe.out);
	return (0);
}
