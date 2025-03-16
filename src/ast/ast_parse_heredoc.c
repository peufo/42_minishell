/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 08:36:55 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/16 15:12:11 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_suppress(char *from, char *to, char **line)
{
	char	*tmp;
	char	*newline;
	int		newlen;
	int		first_step;
	int		i;

	i = 0;
	first_step = ft_strlen(*line) - ft_strlen(from);
	newlen = first_step + ft_strlen(to);
	newline = ft_calloc(newlen, 1);
	tmp = ft_strdup(*line);
	while (i < first_step)
	{
		newline[i] = tmp[i];
		i++;
	}
	while (i < newlen)
	{
		newline[i] = tmp[i];
	}
}

static void	take_heredoc_out(char **line, t_input *input, int index)
{
	bool	dquote;
	bool	squote;
	char	*cursor;
	char	*newline;
	char	*from;

	dquote = false;
	squote = false;
	cursor = ft_strdup(*line);
	while (*cursor)
	{
		check_quotes(*cursor, &dquote, &squote);
		if (!dquote && !squote && check_redir(cursor))
		{
			from = cursor;
			while (*cursor == '<' || ft_isspace(*cursor))
				cursor++;
			while (ft_isalnum(*cursor))
				cursor++;
			ft_suppress(from, cursor, line);
		}
		else
			cursor++;
	}
	free(cursor);
}

static void	str_to_file(t_ast *node, t_input *input, int start)
{
	int		index;
	char	*name;


	index = ft_itoa(start);
	name = ft_strjoin("heredoc_", index);
	node->heredoc.fd_in = open(name, O_CREAT | O_WRONLY | O_TRUNC);
	if (node->heredoc.fd_in == -1)
		throw(node, (char *[]){"Fuck heredocs\n", NULL});
	write(node->heredoc.fd_in,
			input->redir_input[start],
			ft_strlen(input->redir_input[start]));
	free(index);
	free(name);
	close(node->heredoc.fd_in);
}

void	ast_parse_heredoc(t_ast *node)
{
	int		count_from;
	int		redir_in_node;
	int		start;
	int		end;
	char	*tmp;

	printf("Line in heredoc parse :\n%s\n", node->line);
	return ;
	tmp = ft_strchrstr(node->shell->line, node->line);
	redir_in_node = count_redir_in_line(node->shell, node->line, 0, 0);
	if (redir_in_node == 0)
		return ;
	count_from = count_redir_in_line(node->shell, tmp, 0, 0);
	start = node->shell->input.nb_redir - count_from;
	end = redir_in_node + start;
	while (start < end)
		start++;
	str_to_file(node, &node->shell->input, start);
	take_heredoc_out(&node->line, &node->shell->input, start);
}
