/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:23:25 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 17:35:08 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_process_status(char *start, t_sh *shell)
{
	pid_t	status;

	debug(shell, "\n INTO PROCESS STATUS \n");
	while (ft_isalnum(start[shell->lex.len]) || start[shell->lex.len] == '?')
		shell->lex.len++;
	if (shell->lex.len > 0)
	{
		shell->lex.varname = ft_substr(start, 0, shell->lex.len);
		status = get_the_pid(shell->lex.varname);
		free(shell->lex.varname);
		if (status)
		{
			shell->lex.varname = ft_itoa(status);
			lexer_add_token(TOKEN_VAR_STATUS, shell->lex.varname, shell);
			free(shell->lex.varname);
		}
		else
			lexer_add_token(TOKEN_VAR_STATUS, ft_strdup("0"), shell);
	}
	shell->lex.cursor += shell->lex.len;
}

void	lexer_skip_whitespace(t_sh *shell)
{
	debug(shell, "\n INTO SKIP SPACE \n");
	while (*shell->lex.cursor && ft_isspace(*shell->lex.cursor))
		shell->lex.cursor++;
}

void	lexer_skip_comment(t_sh *shell)
{
	debug(shell, "\n INTO SKIP COMMENT \n");
	if (*shell->lex.cursor == '#')
	{
		while (*shell->lex.cursor)
			shell->lex.cursor++;
	}
}

void	lexer_add_token(char *type, char *value, t_sh *shell)
{
	int	size;

	size = ft_strlen(shell->line);
	debug_tokenisation(shell, type, value);
	if (shell->lex.nbt >= size)
		return (throw_error("token limit exceeded\n", __FILE__, __LINE__));
	if (!shell->lex.toks)
		shell->lex.toks = malloc(size * sizeof(char *));
	if (!shell->lex.toks)
		return (throw_error("malloc problem in :\n", __FILE__, __LINE__));
	shell->lex.toks[shell->lex.nbt] = ft_strdup(value);
	shell->lex.nbt++;
	free(value);
}
	/*
		shell->lex.toktypes[shell->lex.nbt] = ft_strdup(type);


	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return ;
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return ;
	}
	ft_lstadd_back(&lexer->tokens, ft_lstnew(token));
}*/

void	lex_free(t_sh *shell)
{
	int	dcount;

	dcount = 0;
	debug(shell, "hello i'm in lexfree\n");
	if (!shell->lex.toks)
		return (debug(shell, "No lexer to free\n"));
	debug(shell, "lexfree1\n");
	while (dcount < shell->lex.nbt)
		free(shell->lex.toks[dcount++]);
	debug(shell, "lexfree2\n");
	free(shell->lex.toks);
	debug(shell, "lexfree5\n");
	shell->lex.toks = NULL;
	shell->lex.nbt = 0;
}
/*t_list	*current;
	t_list	*next;
	t_token	*token;
	t_lexer	*lexer;

	lexer = &shell->lexer;
	if (!lexer || !lexer->tokens)
		return ;
	current = lexer->tokens;
	while (current)
	{
		next = current->next;
		token = (t_token *)current->content;
		if (token)
		{
			if (token->value)
				free(token->value);
			free(token);
		}
		free(current);
		current = next;
	}
	lexer->tokens = NULL;
}
*/