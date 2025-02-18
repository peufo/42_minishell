/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_action_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:13:28 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/18 08:20:13 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_var(t_sh *shell)
{
	char	*value;

	value = env_get(shell, shell->lexer.varname.value);
	string_free(&shell->lexer.varname);
	if (value)
		string_push_str(&shell->lexer.token, value);
}

void	lexer_action_expand_var(t_sh *shell)
{
	if (!shell->lexer.varname.value)
		string_push_str(&shell->lexer.token, "$");
	else if (!ft_strcmp(shell->lexer.varname.value, "?"))
		string_push_str(&shell->lexer.token, "TODO: EXIT_STATUS");
	else
		expand_var(shell);
	if (*(shell->lexer.cursor) != '\0')
		shell->lexer.cursor++;
}

void	lexer_action_expand_var_end_token(t_sh *shell)
{
	lexer_action_expand_var(shell);
	lexer_action_end_token(shell);
}
