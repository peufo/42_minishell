/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geters.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:23:40 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 12:23:41 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pars_get_type(int type)
{
	(void)type;
	return (0);
}

int	pars_get_op(char *type)
{
	(void)type;
	return (AST_OP_NULL);
}

int	pars_get_dir(int type)
{
	(void)type;
	return (0);
}

void	pars_get_position(t_ast *ast, t_list *elements)
{
	int	i;

	i = 0;
	while (i < ast->cursor)
	{
		elements->content = elements->next;
		i++;
	}
}
