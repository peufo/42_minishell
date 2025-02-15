/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:24:16 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/15 13:55:14 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(t_sh *shell)
{
	int	pare_feu;

	if (!shell->lexer.tokens)
		return ;
	shell->ast = ft_calloc(1, sizeof(t_ast));
	if (!shell->ast)
		return (throw_error("Maloc failed \n", __FILE__, __LINE__));
	shell->ast->args = string_array_dup(shell->lexer.tokens);
	pare_feu = check_for_simple_pars(shell, shell->lexer.tokens);
	if (!pare_feu)
		return (throw_error("Line too complex\n", __FILE__, __LINE__));
	else if (pare_feu == 1)
		return (debug(shell, "Only words\n"));
	shell->ast->args = parse_collector(shell->lexer.tokens);
	debug_new_tokens(shell, shell->ast->args);
	shell->ast = parse_handle_script(shell->ast->args, shell);
	debug_ast(shell);
}
