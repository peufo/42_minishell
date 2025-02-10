/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:10:01 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/10 15:55:03 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_simple_pars(t_sh *shell, char **toks)
{
	int		i;
	t_atype	type;

	i = 0;
	while (toks[i])
	{
		type = pars_get_type(toks[i++]);
		debug_arr(shell, (char *[]){"type is :", ft_itoa(type), "\n", NULL});
		if (type == AST_SUBSHELL)
			return (debug(shell, "ast ultime\n"), 0);
		else if (type != AST_COMMAND && type != AST_END)
			return (debug(shell, "ast++\n"), 2);
	}
	return (debug(shell, "simple AST\n"), 1);
}

void	check_list_content(t_sh *shell, t_list *lst)
{
	t_list	*node;

	node = lst;
	if (!node)
		return (throw_error("lst is null", __FILE__, __LINE__));
	while (node->content != NULL)
	{
		debug(shell, (char *)node->content);
		node = node->next;
	}
}
