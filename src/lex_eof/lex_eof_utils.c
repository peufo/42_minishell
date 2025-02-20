/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:02:13 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/20 11:19:34 by dyodlm           ###   ########.fr       */
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
	printf("Token looking : %s\n", shell->lexer.tokens[i - 1]);
	type = parse_get_type(shell->lexer.tokens[i - 1]);
	printf("Last type is : %d\n", type);
	return (type);
}

void	sub_last_token(t_sh *shell, char ***ntoks)
{
	(void)shell;
	(void)ntoks;
}
