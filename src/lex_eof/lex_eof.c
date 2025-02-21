/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:36:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/21 10:36:25 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_eof_free(t_sh *shell, t_lexer *lex)
{
	if (!lex)
		return (lex_free(shell));
	lex_free(shell);
}

static void stack_to_buffer(char **buffer, char ***new_tokens)
{
	size_t	i;
	int		size;
	size_t	tlen;

	i = 0;
	tlen = 0;
	if (!new_tokens || !*new_tokens)
		return ;
	size = string_array_len(*new_tokens);
	while (size-- > 0 && new_tokens && (*new_tokens)[i])
		tlen += ft_strlen((*new_tokens)[i++]);
	i = 0;
	*buffer = ft_calloc(1, tlen + 1);
	if (!*buffer)
		return ;
	size = string_array_len(*new_tokens);
	while (size-- > 0 && new_tokens && (*new_tokens)[i])
	{
		if (ft_strlcat(*buffer, (*new_tokens)[i], tlen + 1) >= tlen + 1)
			break ;
		i++;
	}
}


static void	stack_new_input(char **buffer, t_lexer *lex, char ***new_tokens, t_sh *shell)
{
	int	i;

	i = 0;
	(void)shell;
	if (!*new_tokens)
	{
		*new_tokens = ft_calloc(1, sizeof(char *));
		if (!*new_tokens)
			return ;
	}
	while (lex->tokens && lex->tokens[i])
		string_array_push(new_tokens, lex->tokens[i++]);
	stack_to_buffer(buffer, new_tokens);
}

static void	lex_eof_read_input(t_sh *shell, t_lexer *lex, char ***ntoks, int state)
{
	char	*line;
	char	*readline_buffer;

	readline_buffer = NULL;
	while (1)
	{
		lex->cursor = readline("EOF>");
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
		stack_new_input(&readline_buffer, lex, ntoks, shell);
		if (check_end_in_line(line, state))
			return (add_history(readline_buffer), free(line));
		free(readline_buffer);
		free(line);
		line = NULL;
		readline_buffer = NULL;
	}
}

void	lex_eof(t_sh *shell, int entry_state)
{
	t_lexer		lexer;
	char		**ntoks;
	int			i;

	i = 0;
	ntoks = NULL;
	ft_memset(&lexer, 0, sizeof(t_lexer));
	lex_eof_read_input(shell, &lexer, &ntoks, entry_state);
	if (shell->lexer.tokens && entry_state <= AST_COMMAND)
	{
		if (shell->lexer.token.value)
			string_array_push(&shell->lexer.tokens, shell->lexer.token.value);
		sub_last_token(shell, &ntoks);
		while (ntoks[i])
			string_array_push(&shell->lexer.tokens, ntoks[i++]);
	}
	else
	{
		if (!shell->lexer.tokens)
			shell->lexer.tokens = ft_calloc(1, sizeof(ntoks));
		while (ntoks && ntoks[i])
			string_array_push(&shell->lexer.tokens, ntoks[i++]);
	}
	debug_tokens(shell);
}
