/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:24:16 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/20 06:25:44 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(t_sh *shell)
{
	int		pare_feu;
	char	**args;
	char	**args_tmp;

	args = NULL;
	args_tmp = NULL;
	if (!shell->lexer.tokens)
		return ;
	shell->ast = parse_init_ast(shell);
	shell->ast->args = string_array_dup(shell->lexer.tokens);
	pare_feu = check_for_simple_pars(shell, shell->lexer.tokens);
	if (!pare_feu || pare_feu == 1)
		return (debug(shell, "very simple or very complex\n"));
	string_array_free(&shell->ast->args);
	free(shell->ast);
	shell->ast = NULL;
	args = string_array_dup(shell->lexer.tokens);
	args_tmp = parse_collector(args);
	debug_new_tokens(shell, args_tmp);
	shell->ast = parse_handle_script(args_tmp, shell);
	debug_ast(shell);
}
