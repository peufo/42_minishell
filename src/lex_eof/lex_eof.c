/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:36:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/21 07:00:27 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_eof_free(t_sh *shell, t_lexer *lex)
{
	if (!lex)
		return (lex_free(shell));
	lex_free(shell);
}

static void	stack_to_buffer(char **buffer, char ***new_tokens)
{
	t_utils	u;

	ft_bzero(&u, sizeof(t_utils));
	while (*new_tokens[u.i])
	{
		while (*new_tokens[u.i][u.j++])
			u.x++;
		u.i++;
		u.x += 1;
		u.j = 0;
	}
	*buffer = malloc(u.x + 1);
	if (!*buffer)
		return ;
	while (*new_tokens[u.j])
	{
		ft_strlcat(*buffer, *new_tokens[u.i++], u.x + 1);
		ft_strlcat(*buffer, "\n", u.x + 1);
	}
}

static void	stack_new_input(char **buffer, t_lexer *lex, char ***new_tokens)
{
	t_utils	u;
	char	**tmp;

	tmp = NULL;
	ft_bzero(&u, sizeof(t_utils));
	if (!*new_tokens)
		new_tokens = ft_calloc(1, sizeof(lex->tokens));
	else
		tmp = ft_calloc(1, sizeof(lex->tokens));
	if (!tmp || !new_tokens)
		return ;
	while (lex->tokens[u.i])
		string_array_push(&tmp, lex->tokens[u.i++]);
	if (!tmp)
		while (lex->tokens[u.i])
			string_array_push(new_tokens, lex->tokens[u.i++]);
	else
		while (tmp[u.j])
			string_array_push(new_tokens, tmp[u.j++]);
	stack_to_buffer(buffer, new_tokens);
	string_array_free(&tmp);
	string_array_free(&lex->tokens);
}


static void	lex_eof_read_input(t_sh *shell, t_lexer *lex, char ***ntoks, int state)
{
	char	*readline_buffer;

	readline_buffer = NULL;
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
		stack_new_input(&readline_buffer, lex, ntoks);
		if (check_end_in_line(lex->cursor, state))
			return (add_history(readline_buffer), lex_eof_free(shell, lex));
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
		while (ntoks[i])
			string_array_push(&shell->lexer.tokens, ntoks[i++]);
	}
	return (string_array_free(&ntoks));
}
