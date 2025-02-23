/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:14:54 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/23 18:37:04 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_and(t_ast *node)
{
	if (exec_ast(node->children[0]))
		return (node->children[0]->status);
	return (exec_ast(node->children[1]));
}

int	exec_or(t_ast *node)
{
	if (!exec_ast(node->children[0]))
		return (0);
	return (exec_ast(node->children[1]));
}
