/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:02:13 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/21 11:08:40 by dyodlm           ###   ########.fr       */
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

int	lex_eof_get_last_type(t_sh *shell)
{
	int		i;
	t_atype	type;

	i = 0;
	if (!shell->lexer.tokens)
		return (AST_OP_NULL);
	while (shell->lexer.tokens[i])
		i++;
	type = parse_get_type(shell->lexer.tokens[i - 1]);
	return (type);
}

void	sub_last_token(t_sh *shell, char ***ntoks)
{
	int		i;
	char	*token;

	i = 0;
	token = NULL;
	if (shell->lexer.token.value)
		token = ft_strjoin(shell->lexer.token.value, *ntoks[i++]);
	string_array_push(&shell->lexer.tokens, token);
	while (ntoks[i])
		string_array_push(&shell->lexer.tokens, *ntoks[i++]);
}
