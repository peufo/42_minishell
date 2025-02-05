/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:24:16 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/05 14:44:31 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_free(t_sh *shell)
{
	(void)shell;
}

void	parse(t_sh *shell)
{
	if (!shell->lexer.tokens)
	{
		shell->ast.args = NULL;
		return ;
	}
	shell->ast.type = AST_COMMAND;
	shell->ast.args = shell->lexer.tokens;
	if (ft_lstsize(shell->ast.args) == 1)
		return ;
}
