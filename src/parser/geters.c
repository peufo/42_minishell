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

int	pars_get_type(t_sh *shell, char *tok)
{
	int				i;
	static char		*find[] = {
		"(", ")", "<", "<<", ">>", ">", "&&", "||", "|", NULL
	};

	i = 0;
	while (find[i] != NULL)
	{
		if (ft_strncmp(find[i], tok, ft_strlen(tok)) == 0)
			return (i);
		i++;
	}
	(void)shell;
	return (i);
}

int	pars_get_op(char *type, t_sh *shell)
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

	(void)shell;
	i = 0;
	while (find[i])
	{
		if (ft_strncmp(find[i], type, ft_strlen(type)) == 0)
			return (i);
		i++;
	}
	return (AST_OP_NULL);
}

int	pars_get_dir(int type, t_sh *shell)
{
	(void)shell;
	(void)type;
	return (0);
}

int	pars_get_position(t_list *elements, t_sh *shell)
{
	int	i;

	(void)shell;
	i = 0;
	while (i < shell->ast.cursor)
	{
		elements->content = elements->next;
		i++;
	}
	return (i);
}
