/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:06:38 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/26 13:47:22 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_spaces(char *cursor)
{
	while (ft_isspace(*cursor))
		cursor++;
}

void	init_error_checker(char **cursor, char **head, t_sh *shell)
{
	*cursor = ft_strdup(shell->line);
	*head = *cursor;
	skip_spaces(*cursor);
}

void	error_display(t_sh *shell, char *error)
{
	throw_shell(shell, (char *[]){"Your syntax is shit. What's with <<",
		error, ">> ?", NULL});
}

bool	is_eof_token(char *token, bool in_eof)
{
	short int	i;
	static char	*eof_tok[] = {"|", "&&", "||", NULL};

	i = 0;
	if (!in_eof)
		return (false);
	while (eof_tok[i] && ft_strncmp(token, eof_tok[i], ft_strlen(token)))
		i++;
	return ((eof_tok[i]));
}
