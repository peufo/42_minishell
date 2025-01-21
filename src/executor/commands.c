/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:41:37 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/21 19:21:23 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_free(t_cmd **cmd)
{
	ft_lstclear(&(*cmd)->args, free);
	free(*cmd);
	*cmd = NULL;
}

//TODO: Interpret pipe and redirection and return an execution structure
t_cmd	*command_from(t_list *tokens)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	if (tokens)
	{
		cmd->executable = tokens->content;
		cmd->args = tokens;
	}
	cmd->pipe.in = STDIN_FILENO;
	cmd->pipe.out = STDOUT_FILENO;
	return (cmd);
}
