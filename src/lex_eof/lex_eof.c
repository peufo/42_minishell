/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 04:36:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/25 05:04:58 by dyodlm           ###   ########.fr       */
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
	int		i;

	i = 0;
	toks = lex->tokens;
	if (!toks || !*toks)
		return (debug(shell, "No toks\n"));
	while (toks[i])
	{
		debug(shell, "\nToken is :");
		debug(shell, toks[i++]);
		debug(shell, "\n");
	}
}

static bool	check_buffer_and_last_token(char *buffer, t_lexer *lexer, t_sh *shell, char *line)
{
	int	i;
	int	newstate;
	int	type;

	i = 0;
	type = 0;
	newstate = 0;
	debug(shell, "\ntokens of lexer in checker :");
	debug_ntok(shell, lexer);
	while (lexer->tokens && lexer->tokens[i])
		i++;
	if (i == 0)
		return (true);
	type = parse_get_type(lexer->tokens[i - 1]);
	if (type <= 1)
		newstate = check_string(buffer);
	if (line && check_end_in_line(line, shell->lexer.entry_state, type))
		return (true);
	if (!buffer)
		return (true);
	if (newstate)
		return (true);
	shell->lexer.entry_state = newstate;
//	printf("buffer is false\n");
	return (false);
}

static bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
		if (!ft_isspace(line[i++]))
			return (0);
	return (1);
}

static void	lex_eof_read_input(t_sh *shell, t_lexer *lex)
{
	char	*line;
	char	*stack;
	char	*tmp;
	char	*readline_buffer;

	line = NULL;
	tmp = NULL;
	stack = NULL;
	readline_buffer = NULL;
	while (1)
	{
		while (!line || *line)
		{
			if (shell->lexer.entry_state > 1 || lex_eof_get_last_type(shell))
				lex->cursor = readline("EOF >");
			if (!lex->cursor)
				shell_exit(shell);
			line = ft_strdup(lex->cursor);
			if (line && is_empty_line(line))
				line = NULL;
			else
				break ;
		}
	//	debug(shell, "\nNEW EOF\n\n");
		while (*(lex->cursor))
		{
	//		debug(shell, "\nquotes\n");
			lex_eof_process_quotes_and_var(shell, lex);
	//		debug(shell, "\nwhitespace\n");
			lexer_eof_skip_whitespace(shell, lex);
	//		debug(shell, "\ncomment\n");
			lexer_eof_skip_comment(shell, lex);
	//		debug(shell, "\npar\n");
			lex_eof_process_parenthesis(shell, lex);
	//		debug(shell, "\redir\n");
			lex_eof_process_redirection(shell, lex);
	//		debug(shell, "\ngates\n");
			lex_eof_process_gate_and_pipe(shell, lex);
	//		debug(shell, "\n out of loop\n");
		}
		debug_arr(shell, (char *[]){"State is ", ft_itoa(shell->lexer.entry_state), "\n", NULL});
		debug_ntok(shell, lex);
		if (shell->line)
			readline_buffer = ft_strdup(shell->line);
		stack_new_input(&readline_buffer, lex, line);
	//	debug(shell, "keeping up\n");
		if (shell->line)
		{
			free(shell->line);
			shell->line = NULL;
		}
	//	printf("Type is : %d\n", shell->lexer.entry_state);
		if (check_buffer_and_last_token(readline_buffer, lex, shell, line) && check_end_in_line(line, shell->lexer.entry_state, lex_eof_get_last_type(shell)))
		{
	//		printf("Type is : %d\n", shell->lexer.entry_state);
			shell->lexer.entry_state = 0;
			if (tmp != NULL)
				free(tmp);
			tmp = ft_strjoin(readline_buffer, stack);
			add_history(readline_buffer);
			return ;
		}
		if (lex->token.value)
		{
//			debug(shell, "ca bug sale\n");
			if (!stack && lex->token.value)
				stack = ft_strdup(shell->lexer.token.value);
//			debug(shell, "step1\n");
			if (!lex->tokens)
				lex->tokens = ft_calloc(2, sizeof(char *));
//			debug(shell, "step2\n");
			tmp = ft_strjoin(stack, lex->token.value);
//			debug(shell, "step2.2\n");
			lex->tokens[0] = ft_strdup(tmp);
//			debug(shell, "step3\n");
			if (stack && *lex->tokens)
			{
				free(stack);
				stack = ft_strdup(*lex->tokens);
			}
//			debug(shell, "finalement pas\n");
		}
		free(line);
		line = NULL;
	}
}

void	lex_eof(t_sh *shell, int entry_state)
{
	t_lexer		lexer;

	if (!shell->lexer.tokens)
		shell->lexer.tokens = ft_calloc(1, sizeof(char *));
	shell->lexer.entry_state = entry_state;
	//printf("Data : %s \n TYpe : %d\n", shell->lexer.token.value, shell->lexer.entry_state);
	while (shell->lexer.entry_state > 1)
	{
	//	printf("Type is : %d\n", shell->lexer.entry_state);
		ft_memset(&lexer, 0, sizeof(t_lexer));
		lex_eof_read_input(shell, &lexer);
		debug_new_tokens(shell, lexer.tokens);
		debug(shell, "let's sub\n");
		sub_last_token(shell, &lexer);
		debug(shell, "good sub\n");
		shell->lexer.entry_state = lex_eof_get_last_type(shell);
		debug_arr(shell, (char *[]){"State in handler is ", ft_itoa(shell->lexer.entry_state), "\n", NULL});

	}
	debug(shell, "\n\nOUT\n\n");
	if (string_array_len(shell->lexer.tokens) <= 1 && shell->lexer.token.value)
		string_array_push(&shell->lexer.tokens, ft_strdup(shell->lexer.token.value));
	else if (string_array_len(shell->lexer.tokens) <= 1 && lexer.token.value)
		string_array_push(&shell->lexer.tokens, ft_strdup(lexer.token.value));
	debug_new_tokens(shell, shell->lexer.tokens);
}
