/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:56:04 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/24 15:03:31 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_new_tokens(t_sh *shell, char **toks)
{
	int	i;

	i = 0;
	while (toks[i] != NULL)
	{
		debug(shell, "\nnew token is :");
		debug(shell, toks[i++]);
	}
	debug(shell, "\n\n");
}

void	debug_two_lists(t_sh *shell, t_list *l1, t_list *l2)
{
	t_list	*lst;

	if (!l1 && !l2)
		return ;
	if (l1)
		lst = l1;
	else
		lst = l2;
	while (lst != NULL)
	{
		debug(shell, "\nelement :");
		debug(shell, (char *)lst->content);
		lst = lst->next;
	}
	debug(shell, "\n");
	if (l1)
	{
		lst = l2;
		debug_two_lists(shell, NULL, lst);
	}
	debug(shell, "end of debug list\n");
}

void	debug_input(t_sh *shell)
{
	debug_arr(shell, (char *[]){
		"============\n",
		"INPUT: ",
		shell->line,
		"\n",
		NULL
	});
}
