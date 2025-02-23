/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:36:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/23 10:06:17 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_eof_free(t_sh *shell, t_lexer *lex)
{
	if (!lex)
		return (lex_free(shell));
	lex_free(shell);
}

static void stack_to_buffer(char **buffer, char *line)
{
	char	*tmp;
	size_t	tlen;

	if (!line)
		return ;
	tlen = ft_strlen(line) + 2;
	if (buffer && *buffer)
		tlen += ft_strlen(*buffer);
	tmp = ft_calloc(1, tlen + 1);
	if (!tmp)
		return ;
	if (buffer && *buffer)
	{
		ft_strlcat(tmp, ft_strdup(*buffer), tlen + 1);
		ft_strlcat(tmp, ft_strdup("\n"), tlen + 1);
	}
	ft_strlcat(tmp, line, tlen + 1);
	free(*buffer);
	*buffer = tmp;
	printf("buffer is : %s\n", *buffer);
}

static void	stack_new_input(char **buffer, t_lexer *lex, char ***new_tokens, char *line)
{
	int	i;

	i = 0;
	if (!*new_tokens)
	{
		*new_tokens = ft_calloc(1, sizeof(char *));
		if (!*new_tokens)
			return ;
	}
	while (lex->tokens && lex->tokens[i])
		string_array_push(new_tokens, lex->tokens[i++]);
	printf("Nb of tokens pushed into new tab is : %d\n", i);
	stack_to_buffer(buffer, line);
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

static void	lex_eof_read_input(t_sh *shell, t_lexer *lex, char ***ntoks, int state)
{
	char	*line;
	char	*readline_buffer;

	readline_buffer = NULL;
	while (1)
	{
		if (lex_eof_get_last_type(shell) || shell->lexer.entry_state > 1)
		{
			debug(shell, "\nWoo new line !\n");
			lex->cursor = readline("EOF >");
		}
		if (!lex->cursor && !shell->lexer.tokens)
			shell_exit(shell);
		line = ft_strdup(lex->cursor);
		printf("\nLINE OF INPUT IS :%s\n", line);
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
