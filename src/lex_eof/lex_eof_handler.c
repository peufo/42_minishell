/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 07:42:21 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/20 04:49:16 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sub_last_token(t_sh *shell, char *new_token)
{
	int	i;

	i = 0;
	while (shell->lexer.tokens[i] != NULL)
		i++;
	free(shell->lexer.tokens[i - 1]);
	shell->lexer.tokens[i - 1] = ft_strdup(new_token);
	free(new_token);
}

bool	check_end_in_line(char *line)
{
	return ((line));
}

void	stack_new_line(char **buffer, t_lexer *lex, char ***new_token)
{
	(void)buffer;
	(void)lex;
	(void)new_token;
}
