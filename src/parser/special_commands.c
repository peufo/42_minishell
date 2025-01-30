/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:23:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 12:23:45 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	look_for_special_commands(t_sh *shell)
{
	char	*line;

	line = shell->lexer.cursor;
	if (!line)
		return ;
	else if (!ft_strncmp(line, "exitshell", 9))
		shell_exit(shell);
}
