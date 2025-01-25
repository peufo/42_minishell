/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:34:52 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/22 15:07:39 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lexer_process_parenthesis(t_lexer *lexer)
{
	if (*lexer->cursor == '(')
	{
		lexer_add_token(lexer, L_PAR_OPEN, "(");
		lexer->cursor++;
	}
	else if (*lexer->cursor == ')')
	{
		lexer_add_token(lexer, L_PAR_CLOSE, ")");
		lexer->cursor++;
	}
}

static void	lexer_process_redirection(t_lexer *lexer)
{
	char	*sta;

	sta = lexer->cursor;
	if (*lexer->cursor == '>' || *lexer->cursor == '<')
	{
		if (*(lexer->cursor + 1) == *lexer->cursor)
			lexer->cursor += 2;
		else
			lexer->cursor++;
		lexer_add_token(lexer, L_RDIR, ft_substr(sta, 0, lexer->cursor - sta));
	}
}

static void	lexer_process_pipe(t_lexer *lexer)
{
	if (*lexer->cursor == '|')
	{
		lexer_add_token(lexer, PIPE, "|");
		lexer->cursor++;
	}
}

static void	lexer_process_word(t_lexer *lexer)
{
	char	*start;

	start = lexer->cursor;
	while (*lexer->cursor && !ft_isspace(*lexer->cursor) && !ft_strchr("()|><"
			, *lexer->cursor))
		lexer->cursor++;
	lexer_add_token(lexer, L_WORD, ft_substr(start, 0, lexer->cursor - start));
}

void	lex(t_sh *shell)
{
	t_lexer	lexer;
	t_token	*token;
	t_list	*tokens;

	ft_memset(&lexer, 0, sizeof(t_lexer));
	lexer.cursor = shell->line;
	lexer.tokens = NULL;
	while (*lexer.cursor)
	{
		look_for_quotes(&lexer);
		lexer_skip_whitespace(&lexer);
		lexer_process_parenthesis(&lexer);
		lexer_process_redirection(&lexer);
		lexer_process_pipe(&lexer);
		if (!ft_isspace(*lexer.cursor) && !ft_strchr("()|><", *lexer.cursor))
			lexer_process_word(&lexer);
	}
	tokens = lexer.tokens;
	while (tokens)
	{
		token = tokens->content;
		printf("TOKEN: Type: %d, Value: %s\n", token->type, token->value.value);
		tokens = tokens->next;
	}
	shell->lexer.tokens = lexer.tokens;
}
