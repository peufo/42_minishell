/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:38:02 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/05 00:00:47 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_sh *shell)
{
	if (!shell->ast.args->next)
		return (0);
	env_unset(shell, shell->ast.args->next->content);
	return (0);
}
