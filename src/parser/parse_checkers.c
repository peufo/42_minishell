/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:10:01 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/12 07:28:06 by dyodlm           ###   ########.fr       */
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
