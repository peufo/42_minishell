/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:07:05 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/03 20:23:23 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*catch_the_redir_code(char *line)
{
	int		i;
	int		len;
	char	*res;
	char	*tmp;

	i = 0;
	len = 0;
	tmp = ft_strrchrstr(ft_strdup(line), "<<");
	while (ft_isspace(tmp[i]) || tmp[i] == '<')
		i++;
	while (ft_isalnum(tmp[i + len]))
		len++;
	res = ft_calloc(len + 1, sizeof(char));
	len = 0;
	while (ft_isalnum(tmp[i]))
		res[len++] = tmp[i++];
	res[len] = '\0';
	return (res);
}

bool	check_for_redir(t_input *input)
{
	if (input->line)
		printf("Line is : %s\n", input->line);
	else
		printf("Fuak\n");
	if (input->state == INPUT_DQUOTE || input->state == INPUT_QUOTE)
		return (false);
	else if (!input->redir_code
		&& ft_strnstr(input->line, "<<", ft_strlen(input->line)))
	{
		printf("getting the code\n");
		input->redir_code = catch_the_redir_code(input->line);
		return (true);
	}
	else if (input->redir_code && !ft_strcmp(input->line, input->redir_code))
		return (false);
	else if (input->redir_code)
		return (true);
	return (false);
}
