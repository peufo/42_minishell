/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_sentinels.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:41:11 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/26 07:27:14 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	did_pipe_sentinel_see(char *line)
{
	int	i;

	i = 1;
	if (!line[0] || line[0] != '|')
		return (false);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if ((line[i] && ft_isalnum(line[i])) || line[1] == '|' || line[i] == '('
		|| line[i] == '<' || line[i] == '>' || line[i] == '\\')
		return (false);
	return (true);
}

bool	did_less_sentinel_see(char *line)
{
	int	i;

	i = 1;
	if (!line[0] || line[0] != '<' || line[0] != '>' || line[i] == '\\')
		return (false);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && ft_isalnum(line[i]))
		return (false);
	return (true);
}

bool	did_great_sentinel_see(char *line)
{
	int	i;

	i = 1;
	if (!line[0] || line[0] != '>')
		return (false);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && ft_isalnum(line[i]))
		return (false);
	return (true);
}

bool	did_other_sentinel_see(char *line)
{
	int	i;

	i = 1;
	if (!line[0] || line[0] != '<')
		return (false);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && ft_isalnum(line[i]))
		return (false);
	return (true);
}

bool	did_logical_sentinel_see(char *line)
{
	int	i;

	i = 1;
	if (!line[0] || line[0] != '&')
		return (false);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && ft_isalnum(line[i]))
		return (false);
	return (true);
}
