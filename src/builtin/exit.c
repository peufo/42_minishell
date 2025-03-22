/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:13:34 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/22 00:46:56 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_llong(char *str)
{
	static char	llong_max[] = "9223372036854775807";
	char		*s;
	int			len;

	len = ft_strlen(str);
	if (len > 19)
		return (false);
	if (len < 19)
	{
		while (*str)
			if (!ft_isdigit(*str++))
				return (false);
		return (true);
	}
	s = llong_max;
	while (*s)
	{
		if (!('0' <= *str && *str <= *s))
			return (false);
		s++;
		str++;
	}
	return (true);
}

int	builtin_exit(t_ast *node)
{
	if (node->shell->is_interactive)
		ft_putstr("exit\n");
	if (string_array_len(node->tokens) > 2)
		return (throw(node, (char *[]){"exit: too many arguments", NULL}), 1);
	if (node->tokens[1])
	{
		if (is_llong(node->tokens[1]))
			node->status = (unsigned char)ft_atoi(node->tokens[1]);
		else
		{
			node->status = 255;
			throw(node, (char *[]){
				"exit: ",
				node->tokens[1],
				": numeric argument required",
				NULL
			});
		}
		node->shell->exit_status = node->status;
	}
	shell_exit(node->shell);
	return (node->shell->exit_status);
}
