/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitstatus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:24:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/18 11:46:25 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	waitstatus(t_ast *node, pid_t pid)
{
	int		wstatus;
	int		status;
	int		sig;
	bool	put_nl;

	waitpid(pid, &wstatus, 0);
	status = WEXITSTATUS(wstatus);
	sig = WTERMSIG(wstatus);
	if (sig == SIGINT)
	{
		put_nl = (node->type != AST_PIPELINE || pid == node->children[0]->pid);
		if (put_nl)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return (130);
	}
	if (sig == SIGQUIT)
		return (131);
	if (status == 22)
		status = 127;
	return (status);
}
