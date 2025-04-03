/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_help_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 08:28:40 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/03 09:21:38 by dyodlm           ###   ########.fr       */
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
	res = NULL;
	tmp = ft_strchrstr(line, "<<");
	if (!tmp)
		return (NULL);
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

void	safe_init_redir_array(t_sh *shell, t_input *input)
{
	int		count;
	bool	dquote;
	bool	squote;

	count = 0;
	dquote = input->state == INPUT_DQUOTE;
	squote = input->state == INPUT_QUOTE;
	if (input->redir_line)
		count = count_redir_in_line(shell, input->redir_line, dquote, squote);
	else if (input->line)
		count = count_redir_in_line(shell, input->line, dquote, squote);
	input->nb_redir = count;
	if (input->redir_input)
		free(input->redir_input);
	input->redir_input = ft_calloc((count + 1), sizeof(char *));
	if (!input->redir_input)
		return ;
	if (input->redir_code)
		free(input->redir_code);
	input->redir_code = ft_calloc((count + 1), sizeof(char *));
	if (!input->redir_code)
		return (string_array_free(&input->redir_input));
}

static void	sub_last_line(t_sh *shell, char *end, char *newline)
{
	int	i;

	i = 0;
	if (is_empty_line(shell->input.redir_input[i]))
		return ;
	while (shell->input.redir_input[i] && i < shell->input.nb_redir)
	{
		end = ft_strrchr(shell->input.redir_input[i], '\n');
		if (!end)
		{
			free(shell->input.redir_input[i]);
			shell->input.redir_input[i] = NULL;
			continue ;
		}
		newline = ft_strcut(shell->input.redir_input[i], end);
		if (!check_heredoc_code(end, shell->input.redir_code[i]))
		{
			free(newline);
			i++;
			continue ;
		}
		free(shell->input.redir_input[i]);
		shell->input.redir_input[i++] = newline;
	}
}

void	checkout_from_redir(t_sh *shell)
{
	int		i;
	char	*end;
	char	*newline;
	char	**vars;

	i = 0;
	end = NULL;
	vars = NULL;
	newline = NULL;
	if (!shell->input.redir_input || !shell->input.redir_input[0])
		return ;
	sub_last_line(shell, end, newline);
	while (shell->input.redir_input[i] && i < shell->input.nb_redir)
	{
		find_vars_in_line(&shell->input.redir_input[i], &vars);
		expand_vars_in_line(shell, &shell->input.redir_input[i++], &vars);
	}
}
