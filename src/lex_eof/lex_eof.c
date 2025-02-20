/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:36:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/20 11:21:28 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_eof_free(t_sh *shell, t_lexer *lex)
{
	(void)lex;
	if (shell->lexer.tokens)
		string_array_free(&shell->lexer.tokens);	
}

static bool	check_end_in_line(char *line)
{
	int	i;

	i = 0;
	(void)i;
	return ((line));
}

static void	stack_new_line(char **buffer, t_lexer *lex, char ***new_token)
{
	t_utils	u;

	ft_bzero(&u, sizeof(t_utils));
	while (*new_token[u.i])
	{
		while (*new_token[u.i][u.j++])
			u.x++;
		u.i++;
		u.x += 1;
		u.j = 0;
	}
	*buffer = malloc(u.x + 1);
	if (!*buffer)
		return ;
	while (*new_token[u.j])
	{
		ft_strlcat(*buffer, *new_token[u.i++], u.x + 1);
		ft_strlcat(*buffer, "\n", u.x + 1);
	}
	(void)lex;
}


static void	lex_eof_read_input(t_sh *shell, t_lexer *lex, char ***ntoks)
{
	char	*buffer;

	buffer = NULL;
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
		stack_new_line(&buffer, lex, ntoks);
		if (check_end_in_line(lex->cursor))
			break ;
	}
	add_history(buffer);
}

void	lex_eof(t_sh *shell, int entry_state)
{
	int			i;
	char		**ntoks;
	t_lexer		lex;

	i = 0;
	ntoks = NULL;
	printf("HHELLLOO!\n");
	ft_memset(&lex, 0, sizeof(t_lexer));
	lex_eof_read_input(shell, &lex, &ntoks);
	if (shell->lexer.tokens && entry_state == AST_COMMAND)
	{
		sub_last_token(shell, &ntoks);
		while (ntoks[i])
			string_array_push(&shell->lexer.tokens, ntoks[i++]);
	}
	else
	{
		shell->lexer.tokens = string_array_dup(ntoks);
	}
	return (string_array_free(&ntoks));
}
