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

void	lexer_process_status(t_lexer *lexer, char *start, t_sh *shell)
{
	pid_t	status;

	debug(shell, "\n INTO PROCESS STATUS \n");
	while (ft_isalnum(start[lexer->len]) || start[lexer->len] == '?')
		lexer->len++;
	if (lexer->len > 0)
	{
		lexer->varname = ft_substr(start, 0, lexer->len);
		status = get_the_pid(lexer->varname);
		free(lexer->varname);
		if (status)
		{
			lexer->varname = ft_itoa(status);
			lexer_add_token(lexer, TOKEN_VAR_STATUS, lexer->varname, shell);
			free(lexer->varname);
		}
		else
			lexer_add_token(lexer, TOKEN_VAR_STATUS, ft_strdup("0"), shell);
	}
	lexer->cursor += lexer->len;
}

void	lexer_skip_whitespace(t_lexer *lexer, t_sh *shell)
{
	debug(shell, "\n INTO SKIP SPACE \n");
	while (*lexer->cursor && ft_isspace(*lexer->cursor))
		lexer->cursor++;
}

void	lexer_skip_comment(t_lexer *lexer, t_sh *shell)
{
	debug(shell, "\n INTO SKIP COMMENT \n");
	if (*lexer->cursor == '#')
	{
		while (*lexer->cursor)
			lexer->cursor++;
	}
}

void	lexer_add_token(t_lexer *lexer, char *type, char *value, t_sh *shell)
{
	debug(shell, "\n INTO ADD_TOKEN \n");
	if (lexer->nbt >= 100)
		return (throw_error("token limit exceeded\n", __FILE__, __LINE__));
	if (!lexer->toktypes)
		lexer->toktypes = malloc(100 * sizeof(char *));
	if (!lexer->toks)
		lexer->toks = malloc(100 * sizeof(char *));
	lexer->toktypes[lexer->nbt] = ft_strdup(type);
	ft_memcpy(lexer->toks, value, (size_t)ft_strlen(value));
}
	/*
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
	if (!shell->lexer.toks || !shell->lexer.toktypes)
		return (debug(shell, "No lexer to free\n"));
	while (dcount < shell->lexer.nbt)
		free(shell->lexer.toks[dcount++]);
	free(shell->lexer.toks);
	dcount = 0;
	while (dcount < shell->lexer.nbt)
		free(shell->lexer.toktypes[dcount++]);
	free(shell->lexer.toktypes);
	shell->lexer.toks = NULL;
	shell->lexer.toktypes = NULL;
	shell->lexer.nbt = 0;
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