/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:06:38 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/25 08:26:08 by dyodlm           ###   ########.fr       */
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
