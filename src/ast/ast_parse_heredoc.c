/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 08:36:55 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/19 08:09:16 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	take_heredoc_out(char **line)
{
	bool	quotes[2];
	char	*cursor;
	char	*from;
	char	*head;

	ft_bzero(&quotes, sizeof(quotes));
	cursor = ft_strdup(*line);
	head = cursor;
	while (*cursor)
	{
		check_quotes(*cursor, &quotes[0], &quotes[1]);
		if (!quotes[0] && !quotes[1] && check_redir(cursor))
		{
			from = cursor;
			while (*cursor == '<' || ft_isspace(*cursor))
				cursor++;
			while (ft_isalnum(*cursor))
				cursor++;
			ft_suppress(from, cursor, line);
			break ;
		}
		else
			cursor++;
	}
	free(head);
}

static void	str_to_file(t_ast *node, t_input *input, int start)
{
	static char	*prefix[] = {"hd1", "hd2", "hd3", "hd4", "hd5", "hd6", NULL};
	static int	files = 0;
	char		*name;

	if (files < 6)
		name = prefix[files++];
	else
	{
		files = 0;
		str_to_file(node, input, start);
	}
	node->heredoc.fd_in = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (node->heredoc.fd_in == -1)
		return (throw(node, (char *[]){"Fuck heredocs\n", NULL}),
			shell_exit(node->shell));
	write(node->heredoc.fd_in,
		input->redir_input[start - 1],
		ft_strlen(input->redir_input[start - 1]));
	string_array_push(&node->heredoc.files_in, ft_strdup(name));
	string_array_push(&node->redir.files_in, ft_strdup(name));
	close(node->heredoc.fd_in);
}

void	ast_parse_heredoc(t_ast *node)
{
	int		count_from;
	int		redir_in_node;
	int		start;
	int		end;
	char	*tmp;

	tmp = NULL;
	if (node->line && node->shell->line)
		tmp = ft_strchrstr(node->shell->line, node->line);
	redir_in_node = count_redir_in_line(node->shell, node->line, 0, 0);
	if (redir_in_node == 0 || !tmp)
		return ;
	count_from = count_redir_in_line(node->shell, tmp, 0, 0);
	start = node->shell->input.nb_redir - count_from;
	end = redir_in_node + start;
	while (start < end)
		start++;
	str_to_file(node, &node->shell->input, start);
	while (count_redir_in_line(node->shell, node->line, 0, 0))
		take_heredoc_out(&node->line);
}
