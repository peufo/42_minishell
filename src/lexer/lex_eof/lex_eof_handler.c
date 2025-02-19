/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 07:42:21 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/19 11:14:08 by dyodlm           ###   ########.fr       */
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

static bool	is_eof_token(char *s, int iter)
{
	
	if ((s[iter] == '"' && !s[iter + 1]) || (s[iter] == '\'' && !s[iter + 1]))
		return (true);
	else if (s[iter + 1] == '<' && s[iter] == '<'  && !s[iter + 2])
		return (true);
	return (false);
}

static bool	check_cursor(t_sh *shell)
{
	int		i;
	char	*line;

	i = 0;
	line = shell->lexer.cursor;
	if (!line)
		return (BASIC_MOD);
	printf("line is :%s\n", line);
	if (1)
		return (BASIC_MOD);
	while (line[i] && ft_isalnum(line[i]) && ft_isspace(line[i]))
	{
		if (is_eof_token(line, i))
			return (BONUS_MOD);
		i++;
	}
	return (BASIC_MOD);
}

static bool	check_end_in_line(char *line)
{
	return ((line));
}

static void	stack_new_line(const char **buffer, t_list *toks, char ***new_token)
{
	(void)buffer;
	(void)toks;
	(void)new_token;
}

void	lex_eof_free(t_sh *shell, t_lexer *lex)
{
	(void)lex;
	if (shell->lexer.tokens)
		string_array_free(&shell->lexer.tokens);	
}

static bool	handle_hard_start(t_sh *shell, t_lexer *lex)
{
	(void)shell;
	(void)lex;
}

static void	lex_eof_read_input(t_sh *shell, t_lexer *lex,
		char ***ntoks, char **buffer)
{
	while (1)
	{
		lex->cursor = readline('>');
		if (!lex->cursor)
			shell_exit(shell);
		errno = false;
		while (*(lex->cursor))
		{
			process_quotes_and_var(shell, lex);
			lexer_eof_skip_whitespace(shell, lex);
			lexer_eof_skip_comment(shell, lex);
			process_parenthesis(shell, lex);
			process_redirection(shell, lex);
			process_gate_and_pipe(shell, lex);
			process_quotes_and_var(shell, lex);
		}
		stack_new_line(buffer, lex->tokens, ntoks);
		add_history(buffer);
		free(*buffer);
		*buffer = NULL;
		if (check_end_in_line(lex->cursor))
			break ;
	}
}

void	lex_eof(t_sh *shell)
{
	t_lexer		lex;
	char		*buffer;
	char		**new_token;

	buffer = NULL;
	new_token = NULL;
	ft_memset(&lex, 0, sizeof(t_lexer));
	if (!lex_eof_check_init(shell))
		return ;
	lex_eof_read_input(shell, &lex, &buffer, &new_token);
	if (shell->lexer.tokens)
		sub_last_token(shell, *new_token);
	else
		shell->lexer.tokens = string_array_dup(new_token);
	return (string_array_free(&new_token));
}
