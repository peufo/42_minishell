/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tokens_find.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:40:59 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/05 14:15:44 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	some_token_start_with(char *cursor, void *data)
{
	char	**tokens;

	tokens = (char **)data;
	while (*tokens)
		if (ft_startwith(cursor, *(tokens++)))
			return (true);
	return (false);
}

static	int	ft_startwhith_data(char *cursor, void *data)
{
	return (ft_startwith(cursor, (char *)data));
}

char	*ast_tokens_find_multi(char *line, char **tokens)
{
	return (ast_tokens_each(line, tokens, some_token_start_with));
}

char	*ast_tokens_find(char *line, char *token)
{
	return (ast_tokens_each(line, token, ft_startwhith_data));
}
