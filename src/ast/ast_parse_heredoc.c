/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 08:36:55 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/16 09:25:21 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	str_to_file(t_ast *node, t_input *input, int start, int end)
{
	(void)node;
	(void)input;
	(void)start;
	(void)end;
}

static void	refine_node_line(t_ast *node, t_input *input)
{
	(void)node;
	(void)input;
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
	count_from = count_redir_in_line(node->shell, tmp, 0, 0);
	start = node->shell->input.nb_redir - count_from;
	end = redir_in_node + start;
	refine_node_line(node, &node->shell->input);
	while (start < end)
		str_to_file(node, &node->shell->input, start++, end);
}
