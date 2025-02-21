/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:36:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/21 09:39:40 by dyodlm           ###   ########.fr       */
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
	size = string_array_len(*new_tokens);
	while (size-- > 0 && new_tokens && (*new_tokens)[i])
		tlen += ft_strlen((*new_tokens)[i++]);
	tlen += i;
	i = 0;
	*buffer = ft_calloc(1, tlen + 1);
	if (!*buffer)
		return ;
	(*buffer)[0] = '\0';
	size = string_array_len(*new_tokens);
	while (size-- > 0 && new_tokens && (*new_tokens)[i])
	{
		if (ft_strlcat(*buffer, (*new_tokens)[i], tlen + 1) >= tlen + 1)
			break ;
		if (ft_strlcat(*buffer, "\n", tlen + 1) >= tlen + 1)
			break ;
		i++;
	}
}


static void	stack_new_input(char **buffer, t_lexer *lex, char ***new_tokens, t_sh *shell)
{
	int	i;

	i = 0;
	debug(shell, "\nno newtoken -->going to malloc\n");
	if (!*new_tokens)
	{
		*new_tokens = ft_calloc(1, sizeof(char *));
		if (!*new_tokens)
			return ;
	}
	debug(shell, "\nmalloc is ok\n");
	while (lex->tokens && lex->tokens[i])
	{
		debug(shell, "\ntoken to be pushed is :");
		debug(shell, lex->tokens[i]);
		string_array_push(new_tokens, lex->tokens[i++]);
	}
	debug(shell, "\nall tokens pushed from lex to newtokens\n");
	stack_to_buffer(buffer, new_tokens);
	debug(shell, "\nLine stacked to buffer\n");
	string_array_free(&lex->tokens);
}


static void	lex_eof_read_input(t_sh *shell, t_lexer *lex, char ***ntoks, int state)
{
	char	*line;
	char	*readline_buffer;

	readline_buffer = NULL;
	while (1)
	{
		debug(shell, "\n===New read of line // new input==\n");
		line = readline("EOF>");
		lex->cursor = line;
		if (!lex->cursor)
			shell_exit(shell);
		while (*(lex->cursor))
		{
			debug(shell, "process_quotes and var\n");
			lex_eof_process_quotes_and_var(shell, lex);
			debug(shell, "process whitespaces\n");
			lexer_eof_skip_whitespace(shell, lex);
			debug(shell, "process comment\n");
			lexer_eof_skip_comment(shell, lex);
			debug(shell, "process_parenthesis\n");
			lex_eof_process_parenthesis(shell, lex);
			debug(shell, "process redirection\n");
			lex_eof_process_redirection(shell, lex);
			debug(shell, "process gate and pipe\n");
			lex_eof_process_gate_and_pipe(shell, lex);
			debug(shell, "process_quotes and var\n");
		}
		debug(shell, "\nLex input read\n-->into stack new_input");
		stack_new_input(&readline_buffer, lex, ntoks, shell);
		if (check_end_in_line(line, state))
			return (add_history(readline_buffer), lex_eof_free(shell, lex));
		free(readline_buffer);
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
	debug(shell, "\nInto lex eof\n-->read_input\n");
	lex_eof_read_input(shell, &lexer, &ntoks, entry_state);
	debug(shell, "\nOut of read input !\n");
	if (shell->lexer.tokens && entry_state <= AST_COMMAND)
	{
		debug(shell, "\nIt is an AST Command logic\n");
		if (shell->lexer.token.value)
			string_array_push(&shell->lexer.tokens, shell->lexer.token.value);
		debug(shell, "last token pushed\n");
		sub_last_token(shell, &ntoks);
		debug(shell, "last token substitution done\n");
		while (ntoks[i])
			string_array_push(&shell->lexer.tokens, ntoks[i++]);
		debug(shell, "\n==Lexer ok==\n");
	}
	else
	{
		debug(shell, "It is an Logical node logiq\n");
		if (!shell->lexer.tokens)
			shell->lexer.tokens = ft_calloc(1, sizeof(ntoks));
		debug(shell, "tokens to be pushed\n");
		while (ntoks && ntoks[i])
		{
			debug(shell, "token pushed !\n");
			string_array_push(&shell->lexer.tokens, ntoks[i++]);
		}
		debug(shell, "\n==Lexer ok==\n");
	}
	debug(shell, "\nOut of lex eof !\n");
	debug_tokens(shell);
	return (string_array_free(&ntoks));
}
