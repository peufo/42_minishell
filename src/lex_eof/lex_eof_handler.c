/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 07:42:21 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/19 13:20:54 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static bool	check_end_in_line(char *line)
{
	return ((line));
}

static void	stack_new_line(char **buffer, t_lexer *lex, char ***new_token)
{
	(void)buffer;
	(void)lex;
	(void)new_token;
}

void	lex_eof_free(t_sh *shell, t_lexer *lex)
{
	(void)lex;
	if (shell->lexer.tokens)
		string_array_free(&shell->lexer.tokens);	
}

static bool	lex_eof_check_init(t_sh *shell)
{
	(void)shell;
	return (false);
}

static void	lex_eof_read_input(t_sh *shell, t_lexer *lex,
		char **buffer, char ***ntoks)
{
	while (1)
	{
		lex->cursor = readline("EOF>");
		if (!lex->cursor)
			shell_exit(shell);
		errno = false;
		while (*(lex->cursor))
		{
			lex_eof_process_quotes_and_var(shell, lex);
			lexer_eof_skip_whitespace(shell, lex);
			lexer_eof_skip_comment(shell, lex);
			lex_eof_process_parenthesis(shell, lex);
			lex_eof_process_redirection(shell, lex);
			lex_eof_process_gate_and_pipe(shell, lex);
			lex_eof_process_quotes_and_var(shell, lex);
		}
		stack_new_line(buffer, lex, ntoks);
		add_history(*buffer);
		free(*buffer);
		*buffer = NULL;
		if (check_end_in_line(lex->cursor))
			break ;
	}
}

void	lex_eof(t_sh *shell, int entry_state)
{
	t_lexer		lex;
	char		*buffer;
	char		**new_token;
	int			last_type;


	buffer = NULL;
	new_token = NULL;
	ft_memset(&lex, 0, sizeof(t_lexer));
	if (!lex_eof_check_init(shell))
		return ;
	last_type = string_array_get_last(&shell->lexer.tokens);
	lex_eof_read_input(shell, &lex, &buffer, &new_token);
	if (shell->lexer.tokens)
		sub_last_token(shell, *new_token);
	else
		shell->lexer.tokens = string_array_dup(new_token);
	(void)last_type;
	(void)entry_state;
	return (string_array_free(&new_token));
}
