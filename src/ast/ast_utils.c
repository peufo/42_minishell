/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:40:59 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/24 14:06:40 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ast_tokens_find(char **tokens, char *token)
{
	char	**cursor;
	int		in_parenthesis;

	in_parenthesis = 0;
	cursor = tokens;
	while (*cursor)
	{
		if (!ft_strcmp(*cursor, "("))
			in_parenthesis++;
		if (!ft_strcmp(*cursor, ")"))
			in_parenthesis--;
		if (!in_parenthesis && !ft_strcmp(*cursor, token))
			break ;
		cursor++;
	}
	if (!*cursor)
		return (NULL);
	return (cursor);
}
