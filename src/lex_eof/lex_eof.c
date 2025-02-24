/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:36:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/24 07:47:44 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_eof_free(t_sh *shell, t_lexer *lex)
{
	if (!lex)
		return (lex_free(shell));
	lex_free(shell);
}

static void	debug_ntok(t_sh *shell, t_lexer *lex)
{
	char	**toks;

	toks = lex->tokens;
	if (!toks || !*toks)
		return ;
	for (int i = 0; toks[i]; i++)
	{
		debug(shell, "\nToken is :");
		debug(shell, toks[i]);
		debug(shell, "\n");
	}
}

static bool	check_buffer(char *buffer)
{
	if (!buffer)
		return (true);
	return (check_string(buffer));
}

static void	lex_eof_read_input(t_sh *shell, t_lexer *lex,
		char ***ntoks, int state)
{
	char	*line;
	char	*readline_buffer;

	readline_buffer = NULL;
	while (1)
	{
		if (shell->lexer.entry_state > 1 || lex_eof_get_last_type(shell))
			lex->cursor = readline("EOF >");
		printf("Cursor is : %s\n", lex->cursor);
		if (!lex->cursor)
			shell_exit(shell);
		line = ft_strdup(lex->cursor);
		while (*(lex->cursor))
		{
			lex_eof_process_quotes_and_var(shell, lex);
			lexer_eof_skip_whitespace(shell, lex);
			lexer_eof_skip_comment(shell, lex);
			lex_eof_process_parenthesis(shell, lex);
			lex_eof_process_redirection(shell, lex);
			lex_eof_process_gate_and_pipe(shell, lex);
		}
		debug_ntok(shell, lex);
		if (shell->line)
			readline_buffer = ft_strdup(shell->line);
		stack_new_input(&readline_buffer, lex, ntoks, line);
		if (shell->line)
		{
			free(shell->line);
			shell->line = NULL;
		}
		if (check_end_in_line(line, state))
			return (add_history(readline_buffer), free(line));
		free(line);
		line = NULL;
		if (check_buffer(readline_buffer))
		{
			shell->lexer.entry_state = 0;
			return (add_history(readline_buffer));
		}
	}
}

void	lex_eof(t_sh *shell, int entry_state)
{
	t_lexer		lexer;
	char		**ntoks;

	ntoks = NULL;
	if (!shell->lexer.tokens)
		shell->lexer.tokens = ft_calloc(1, sizeof(char *));
	shell->lexer.entry_state = entry_state;
	printf("Data : %s \n TYpe : %d\n", shell->lexer.token.value, shell->lexer.entry_state);
	while (shell->lexer.entry_state > 1)
	{
		debug(shell, "\nNew loop in lex_eof\n");
		ft_memset(&lexer, 0, sizeof(t_lexer));
		lex_eof_read_input(shell, &lexer, &ntoks, entry_state);
		debug(shell, "\nInput read ok-->go debug\n");
		debug_new_tokens(shell, lexer.tokens);
		debug(shell, "\nDebug ok-->go push toks\n");
		sub_last_token(shell, &lexer);
		debug(shell, "\nSub ok-->going out\n");
	}
	debug_tokens(shell);
}
