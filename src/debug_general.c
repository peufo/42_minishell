/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:56:04 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/04 14:05:46 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_new_tokens(char **toks)
{
	int	i;

	i = 0;
	if (!toks || !*toks)
		return ;
	while (toks[i] != NULL)
		DEBUG("\nnew token is : %s", toks[i++]);
	DEBUG("\n\n");
}

void	debug_two_lists(t_list *l1, t_list *l2)
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
		DEBUG("\nelement : %s", (char *)lst->content);
		lst = lst->next;
	}
	DEBUG("\n");
	if (l1)
	{
		lst = l2;
		debug_two_lists(NULL, lst);
	}
	DEBUG("end of debug list\n");
}

void	debug_input_struct(t_sh *shell)
{
	t_input	*i;

	i = shell->input;
	if (!i)
		return ;
	DEBUG("\nDEBUG INPUT\n");
	DEBUG("Input line : %s\n", i->line);
	if (i->stack)
		DEBUG("Stack : %s\n", i->stack);
	DEBUG("State : %d\n", i->state);
	DEBUG("Last operator : %d\n", i->last);
	DEBUG("\nABOUT REDIRECTION\n");
	DEBUG("Is redir ? %d\n", i->is_redir);
	DEBUG("Redir code : %s\n", i->redir_code);
	DEBUG("Redir input : %s\n", i->redir_input);
}
