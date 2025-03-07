/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitstatus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:24:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/07 18:47:15 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: handle signals INTERUPT
int	waitstatus(pid_t pid)
{
	int	wstatus;
	int	status;

	waitpid(pid, &wstatus, 0);
	status = WEXITSTATUS(wstatus);
	return (status);
}
