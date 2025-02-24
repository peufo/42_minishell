/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:36:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/24 12:58:26 by dyodlm           ###   ########.fr       */
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

static bool	check_buffer_and_last_token(char *buffer, t_lexer *lexer, t_sh *shell)
{
	int	i;
	int	newstate;
	int	type;

	i = 0;
	newstate = 0;
	if (!buffer)
		return (true);
	while (lexer->tokens && lexer->tokens[i])
		i++;
	if (i == 0)
		return (true);
	type = parse_get_type(lexer->tokens[i - 1]);
	if (type <= 1)
		newstate = check_string(buffer);
	if (newstate)
		return (true);
	shell->lexer.entry_state = newstate;
	printf("buffer is false\n");
	return (false);
}

static void	lex_eof_read_input(t_sh *shell, t_lexer *lex,
		char ***ntoks, int state)
{
	char	*line;
	char	*readline_buffer;

	(void)state;
	readline_buffer = NULL;
	while (1)
	{
		if (shell->lexer.entry_state > 1 || lex_eof_get_last_type(shell))
			lex->cursor = readline("EOF >");
		if (!lex->cursor)
			shell_exit(shell);
		line = ft_strdup(lex->cursor);
		while (*(lex->cursor))
		{
			debug(shell, "\nquotes\n");
			lex_eof_process_quotes_and_var(shell, lex);
			debug(shell, "\nwhitespace\n");
			lexer_eof_skip_whitespace(shell, lex);
			debug(shell, "\ncomment\n");
			lexer_eof_skip_comment(shell, lex);
			debug(shell, "\npar\n");
			lex_eof_process_parenthesis(shell, lex);
			debug(shell, "\redir\n");
			lex_eof_process_redirection(shell, lex);
			debug(shell, "\ngates\n");
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
		printf("Type is : %d\n", shell->lexer.entry_state);
		if (check_buffer_and_last_token(readline_buffer, lex, shell) && check_end_in_line(line, shell->lexer.entry_state))
		{
			printf("Type is : %d\n", shell->lexer.entry_state);
			shell->lexer.entry_state = 0;
			add_history(readline_buffer);
			return ;
		}
		free(line);
		line = NULL;
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
		printf("Type is : %d\n", shell->lexer.entry_state);
		ft_memset(&lexer, 0, sizeof(t_lexer));
		lex_eof_read_input(shell, &lexer, &ntoks, entry_state);
		debug_new_tokens(shell, lexer.tokens);
		sub_last_token(shell, &lexer);
		shell->lexer.entry_state = lex_eof_get_last_type(shell);
	}
	debug(shell, "\n\nOUT\n\n");
	debug_new_tokens(shell, shell->lexer.tokens);
}
