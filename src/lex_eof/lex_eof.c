/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:36:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/20 10:32:50 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	buffer = NULL;
	new_token = NULL;
	printf("HHELLLOO!\n");
	ft_memset(&lex, 0, sizeof(t_lexer));
	lex_eof_read_input(shell, &lex, &buffer, &new_token);
	if (shell->lexer.tokens)
		sub_last_token(shell, *new_token);
	else
		shell->lexer.tokens = string_array_dup(new_token);
	(void)entry_state;
	return (string_array_free(&new_token));
}

void	lex_eof_free(t_sh *shell, t_lexer *lex)
{
	(void)lex;
	if (shell->lexer.tokens)
		string_array_free(&shell->lexer.tokens);	
}
