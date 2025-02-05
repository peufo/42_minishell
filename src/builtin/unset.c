/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:38:02 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/05 14:56:30 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_sh *shell)
{
	if (!shell->ast.args[1])
		return (0);
	env_unset(shell, shell->ast.args[1]);
	return (0);
}
