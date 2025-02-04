/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_action_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:13:28 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/04 21:15:30 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_action_expand_var(t_sh *shell)
{
	char	*value;

	value = get_env(shell, shell->lexer.varname.value);
	string_free(&shell->lexer.varname);
	if (value)
		string_push_str(&shell->lexer.token, value);
	shell->lexer.cursor++;
}

void	lexer_action_expand_var_end_token(t_sh *shell)
{
	lexer_action_expand_var(shell);
	lexer_action_end_token(shell);
}
