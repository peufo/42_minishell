/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 07:42:21 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/19 08:33:33 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	sub_last_token(t_sh *shell, char *new_token)
{
	int	i;

	i = 0;
	while (shell->lexer.tokens[i] != NULL)
		i++;
	free(shell->lexer.tokens[i - 1]);
	shell->lexer.tokens[i - 1] = ft_strdup(new_token);
	free(new_token);
}

static bool	check_line(t_sh *shell, t_string line, char **buffer)
{
	int			start_var;
	t_list		*varnames;

	(void)buffer;
	start_var = 0;
	varnames = NULL;
	if (!line.value)
		return (false);
	line.len = ft_strlen(line.value);
	while (shell->lexer.varname.len != line.len)
	{
		shell->lexer.varname.value = extract_var(shell, line.value, start_var);
		lexer_action_expand_var(shell);
		string_push_str(&shell->lexer.token, shell->lexer.token.value);
		ft_lstadd_back(&varnames, ft_lstnew(&shell->lexer.token.value));
	}
	if (lex_check_end(line.value))
		return (true);
	return (false);
}

static bool	is_eof_token(char *s, int iter)
{
	
	if ((s[iter] == '"' && !s[iter + 1]) || (s[iter] == '\'' && !s[iter + 1]))
		return (true);
	else if (s[iter + 1] == '<' && s[iter] == '<'  && !s[iter + 2])
		return (true);
	return (false);
}

static bool	check_cursor(t_sh *shell)
{
	int		i;
	char	*line;

	i = 0;
	line = shell->lexer.cursor;
	if (!line)
		return (BASIC_MOD);
	while (line[i] && ft_isalnum(line[i]) && ft_isspace(line[i]))
	{
		if (is_eof_token(line, i))
			return (BONUS_MOD);
		i++;
	}
	return (BASIC_MOD);
}

int	lex_check_eof(t_sh *shell)
{
	t_string	line;
	char		*buffer;
	char		*new_token;

	buffer = NULL;
	new_token = NULL;
	ft_bzero(&line, sizeof(t_string));
	if (check_cursor(shell) == BASIC_MOD)
		return (BASIC_MOD);
	if (!check_token(shell))
		return (debug(shell, "\nInput line ok\n\n"), BASIC_MOD);
	while (1)
	{
		ft_putchar_fd('>', STDOUT_FILENO);
		line.value = get_next_line(STDIN_FILENO);
		if (check_line(shell, line, &buffer))
		{
			new_token = ft_strdup(buffer);
			free(buffer);
			break ;
		}
		free(line.value);
	}
	sub_last_token(shell, new_token);
	return (debug(shell, new_token), free(new_token), free((line.value)));
}*/
