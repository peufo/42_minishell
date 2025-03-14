/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_help_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 08:28:40 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/15 09:17:33 by dyodlm           ###   ########.fr       */
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

	dquote = false;
	squote = false;
	if (input->state == INPUT_DQUOTE)
		dquote = true;
	if (input->state == INPUT_QUOTE)
		squote = true;
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

void	check_quotes(char c, bool *dquote, bool *quote)
{
	if (c == '"')
	{
		if (*dquote)
			*dquote = false;
		else
			*dquote = true;
	}
	if (c == '\'')
	{
		if (*quote)
			*quote = false;
		else
			*quote = true;
	}
}

bool	check_redir(char *cursor)
{
	if (cursor && cursor[0] == '<' && cursor[1] == '<')
		return (true);
	return (false);
}

void	checkout_from_redir(t_sh *shell)
{
	if (shell->input.stack)
		shell->line = ft_strdup(shell->input.stack);
	else if (shell->input.line)
		shell->line = ft_strdup(shell->input.line);
}
