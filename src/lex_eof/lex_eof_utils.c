/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:02:13 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/20 05:40:40 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_eof_skip_whitespace(t_sh *shell, t_lexer *lexer)
{
	while (*lexer->cursor && ft_isspace(*lexer->cursor))
		lexer->cursor++;
	(void)shell;
}

void	lexer_eof_skip_comment(t_sh *shell, t_lexer *lexer)
{
	if (*lexer->cursor == '#')
	{
		while (*lexer->cursor)
			lexer->cursor++;
	}
	(void)shell;
}

char	*ft_cut(char *from, char *to)
{
	return (ft_substr(from, 0, to - from));
}

int	string_array_get_last(char ***tokens)
{
	(void)tokens;
	return (0);
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
	if (type != AST_OP_NULL)
		return (type);
	return (0);
}
