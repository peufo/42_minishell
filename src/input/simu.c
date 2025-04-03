/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:24:48 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/03 10:17:41 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ask_for_line(t_input *input, int index)
{
	int		fd;
	char	*line;

	fd = 0;
	printf("Code to check : %s\n", input->redir_code[index]);
	ft_putstr_fd("heredoc>", 1);
	line = get_line(fd);
	if (!line)
		return (true);
	if (!ft_strcmp(line, input->redir_code[index]))
	{
		printf("nice\n");
		return (free(line), true);
	}
	return (free(line), false);
}

static void	make_them_believe(t_sh *shell, char *newline, int count)
{
	int		i;
	t_input	tmp;
	char	*cursor;

	(void)shell;
	i = 0;
	cursor = newline;
	printf("cursor : %s\n", cursor);
	ft_memset(&tmp, 0, sizeof(t_utils));
	get_all_codes(&tmp, cursor);
	printf("Code 1 : %s\n", tmp.redir_code[0]);
	printf("code 2 : %s\n", tmp.redir_code[1]);
	printf("count is : %d\n", count);
	while (i < count)
	{
		if (ask_for_line(&tmp, i))
			i++;
	}
//	input_free(&tmp);
	free(newline);
}

static bool	is_heredoc_valid(char *line)
{
	int	i;

	i = 0;
	if (line && *line)
		line += 2;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (is_empty_line(line))
		return (false);
	return ((ft_isprint(line[i]) && line[i] != '<' && line[i] != '>'
		&& line[i] != '&' && line[i] != '|'));
}

void	simu_heredoc(char *problem, t_sh *shell)
{
	int		count;
	char	*nline;
	char	*cursor;
	char	*tmp;

	cursor = shell->line;
	count = 0;
	while (1)
	{
		tmp = ft_strchrstr(cursor, "<<");
		if (!tmp || !is_heredoc_valid(tmp))
			break ;
		cursor += 2;
	}
	if (tmp)
		nline = ft_strcut(shell->line, tmp);
	count = count_redir_in_line(shell, nline, 0, 0);
	if (count >= 1)
		make_them_believe(shell, nline, count);
	else
		return (free(nline), error_display(shell, problem));
}
