/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitstatus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:24:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/04 15:40:44 by jvoisard         ###   ########.fr       */
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
	put_nl = (node->type != AST_PIPELINE || pid == node->children[0]->pid);
	if (sig == SIGINT && put_nl)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (status == 22)
		status = 127;
	return (status);
}
