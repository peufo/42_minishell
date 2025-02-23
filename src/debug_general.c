/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:56:04 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/23 10:06:57 by dyodlm           ###   ########.fr       */
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

void	debug_tokens(t_sh *shell)
{
	char	**tokens;

	tokens = shell->lexer.tokens;
	if (!tokens)
	{
		debug(shell, "NO TOKENS\n");
		return ;
	}
	debug(shell, "\nTOKENS:\n");
	while (*tokens)
	{
		debug_arr(shell, (char *[]){
			"[",
			*tokens,
			"]\n",
			NULL
		});
		tokens++;
	}
}

void	debug_input(t_sh *shell)
{
	debug_arr(shell, (char *[]){
		"============\n",
		"INPUT: ",
		shell->line,
		NULL
	});
}
