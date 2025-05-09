/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:37:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/30 11:47:09 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_correct_identifier(char *token)
{
	if (!*token)
		return (false);
	if (!ft_isalpha(*token) && *token != '_')
		return (false);
	while (*token)
	{
		if (!ft_isalnum(*token) && *token != '_')
			return (false);
		token++;
	}
	return (true);
}

static char	*take_identifier(char *token)
{
	char	*equal;

	equal = token + 1;
	while (*equal && *equal != '=')
		equal++;
	return (ft_strcut(token, equal));
}

static int	identifier_error(t_ast *node, char *token)
{
	throw(node, (char *[]){
		"export: `",
		token,
		"': not a valid identifier",
		NULL});
	return (1);
}

int	builtin_export(t_ast *node)
{
	char	*identifier;
	char	*value;
	char	**token;

	token = node->tokens + 1;
	if (!*token)
		return (builtin_export_print(node));
	while (*token)
	{
		identifier = take_identifier(*token);
		if (!identifier)
			return (shell_exit(node->shell), 1);
		if (!is_correct_identifier(identifier))
			return (free(identifier), identifier_error(node, *token));
		value = ft_strdup(*(token++));
		if (!value)
		{
			free(identifier);
			shell_exit(node->shell);
			return (1);
		}
		env_set(node->shell, identifier, value);
		free(identifier);
	}
	return (0);
}
