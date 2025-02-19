/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:02:13 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/19 11:54:40 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_eof_stack_totok(t_lexer *lex)
{
	(void)lex;
}

void	lex_eof_free(t_sh *shell)
{
	(void)shell;
}

void	lexer_eof_skip_whitespace(t_lexer *lexer)
{
	while (*lexer->cursor && ft_isspace(*lexer->cursor))
		lexer->cursor++;
}

void	lexer_eof_skip_comment(t_lexer *lexer)
{
	if (*lexer->cursor == '#')
	{
		while (*lexer->cursor)
			lexer->cursor++;
	}
}

char	*ft_cut(char *from, char *to)
{
	return (ft_substr(from, 0, to - from));
}

int	lex_eof_get_last_type(char ***tokens)
{
	int	i;
	int	type;

	i = 0;
	if (!tokens || !*tokens)
		return (-1);
	while (*tokens[i])
		i++;
	type = parse_get_op(*tokens[i - 1]);
	if (type != AST_OP_OR)
		return (type);
	return (0);
}
