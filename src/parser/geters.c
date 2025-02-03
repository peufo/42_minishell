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

int	pars_get_type(int op)
{
	if (op == AST_OP_AND || op == AST_OP_OR)
		return (AST_LOGICAL);
	if (op == AST_OP_DGREAT || op == AST_OP_DLESS
		|| op == AST_OP_GREAT || op == AST_OP_LESS)
		return (AST_REDIRECT);
	return (AST_COMMAND);
}

int	pars_get_op(char *type)
{
	int			i;
	static char	*find[] = {
		"<",
		"<<",
		">",
		">>",
		"||",
		"&&",
		NULL
	};

	i = 0;
	while (find[i])
	{
		if (ft_strncmp(find[i], type, ft_strlen(type)) == 0)
			return (i);
		i++;
	}
	return (AST_OP_NULL);
}

int	pars_get_dir(int type)
{
	(void)type;
	return (0);
}

int	pars_get_position(t_ast *ast, t_list *elements)
{
	int	i;

	i = 0;
	while (i < ast->cursor)
	{
		elements->content = elements->next;
		i++;
	}
	return (i);
}
