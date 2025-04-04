/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:09:57 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/03 06:08:09 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
		if (!ft_isspace(line[i++]))
			return (false);
	return (true);
}

int	count_redir_in_line(t_sh *shell, char *line, bool dquote, bool quote)
{
	char	*head;
	char	*cursor;
	int		count;

	count = 0;
	head = ft_strdup(line);
	cursor = head;
	if (!cursor)
		return (0);
	while (*cursor)
	{
		check_quotes(*cursor, &dquote, &quote);
		if (!dquote && !quote && check_redir(cursor))
		{
			count++;
			while (*cursor == '<' || ft_isspace(*cursor))
				cursor++;
			while (ft_isalnum(*cursor))
				cursor++;
		}
		else
			cursor++;
	}
	(void)shell;
	return (free(head), count);
}

void	transfer_shell_line(t_sh *shell)
{
	if (shell->line2 && !shell->line)
	{
		free(shell->line2);
		shell->line2 = NULL;
	}
	if (!shell->line)
	{
		shell->input.line = NULL;
		return ;
	}
	if (!shell->line)
		return ;
	shell->input.line = ft_strdup(shell->line);
	free(shell->line);
	shell->line = NULL;
}

bool	apply_redir(t_sh *shell, char *copy)
{
	if (!apply_redir_logic(&shell->input, shell))
	{
		shell->line = copy;
		if (shell->line2)
		{
			shell->line = shell->line2;
			return (free(copy), false);
		}
		return (shell_exec(shell), false);
	}
	return (true);
}
