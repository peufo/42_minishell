/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_eof.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 07:42:21 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/18 09:26:12 by dyodlm           ###   ########.fr       */
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

static bool	check_token(t_sh *shell)
{
	return (shell->lexer.token.value[0] == '(' && shell->lexer.state <= 1);
}

static bool	check_line(t_sh *shell, char *line, char **buffer)
{
	if (!line)
		return (false);
	if (lex_check_var(shell, line, buffer))
	{
		//	copier jusqu'a variable dans le buffer + redefinir la ligne
		lexer_action_expand_var(shell);
		//	liberer et concatener jusqu'au guillemet ou \n
	}
	if (lex_check_quotes(shell, line, buffer))
		return (true);
	return (false);
}

void	lex_check_eof(t_sh *shell)
{
	char	*line;
	char	*buffer;
	char	*new_token;

	line = NULL;
	buffer = NULL;
	new_token = NULL;
	if (!check_tokens(shell))
		return (debug(shell, "Input line ok\n"));
	while (1)
	{
		ft_putchar_fd('>', STDIN_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (check_line(shell, line, &buffer))
		{
			new_token = ft_strdup(buffer);
			free(buffer);
			free(line);
			break ;
		}
		free(line);
	}
	sub_last_token(shell, new_token);
	debug(shell, "got the new token\nNew token is :\n");
	return (debug(shell, new_token), free(new_token));
}*/
