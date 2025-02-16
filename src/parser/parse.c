/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:24:16 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/15 17:19:58 by dyodlm           ###   ########.fr       */
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
	shell->ast = ft_calloc(1, sizeof(t_ast));
	if (!shell->ast)
		return (throw_error("Maloc failed \n", __FILE__, __LINE__));
	shell->ast->args = string_array_dup(shell->lexer.tokens);
	pare_feu = check_for_simple_pars(shell, shell->lexer.tokens);
	if (!pare_feu)
		return (throw_error("Line too complex\n", __FILE__, __LINE__));
	else if (pare_feu == 1)
		return (debug(shell, "Only words\n"));
	string_array_free(&shell->ast->args);
	free(shell->ast);
	shell->ast = NULL;
	args = string_array_dup(shell->lexer.tokens);
	args_tmp = parse_collector(args);
	debug_new_tokens(shell, args_tmp);
	shell->ast = parse_handle_script(args_tmp, shell);
	debug_ast(shell);
}
