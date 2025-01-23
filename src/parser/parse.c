/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:24:16 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 15:02:26 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_free(t_sh *shell)
{
	(void)shell;
}

void	parse(t_sh *shell)
{
	t_list	*tokens = shell->lexer.tokens;

	shell->parser.cmd.args = shell->lexer.tokens;
	shell->parser.cmd.pipe.in = STDIN_FILENO;
	shell->parser.cmd.pipe.out = STDOUT_FILENO;
	if ((char *)shell->parser.cmd.args->content)
	{
		(void)tokens;
	}
}