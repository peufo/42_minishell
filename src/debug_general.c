/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:56:04 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/03 20:22:41 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_new_tokens(t_sh *shell, char **toks)
{
	int	i;

	i = 0;
	if (!toks || !*toks)
		return ;
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

void	debug_input_struct(t_sh *shell)
{
	t_input	*i;

	i = shell->input;
	if (!i)
		return ;
	debug(shell, "\nDEBUG INPUT\n");
	debug_arr(shell, (char *[]){"Input line : ", i->line, "\n", NULL});
	if (i->stack)
		debug_arr(shell, (char *[]){"Stack : ", i->stack, "\n", NULL});
	debug_arr(shell, (char *[]){"State : ", ft_itoa(i->state), "\n", NULL});
	debug_arr(shell, (char *[]){
		"Last operator :",
		ft_itoa(i->last),
		"\n",
		NULL
	});
	debug(shell, "\nABOUT REDIRECTION\n");
	debug_arr(shell, (char *[]){
		"Is redir ? ",
		ft_itoa(i->is_redir),
		"\n",
		NULL
	});
	debug_arr(shell, (char *[]){"Redir code : ", i->redir_code, "\n", NULL});
	debug_arr(shell, (char *[]){"Redir input :", i->redir_input, "\n", NULL});
}
