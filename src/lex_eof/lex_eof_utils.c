/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:02:13 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/24 12:40:31 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_get_type(char *tok)
{
	int				i;
	static t_ttype	ttype[] = {
	{"&&", 3},
	{"||", 3},
	{"|", 2},
	{"(", 5},
	{"<", 4},
	{">", 4},
	{">>", 4},
	{"<<", 4},
	{NULL, 0}
	};

	i = 0;
	if (tok == NULL)
		return (AST_NULL);
	while (ttype[i].tok)
	{
		if (!ft_strcmp(ttype[i].tok, tok))
			return (ttype[i].op);
		i++;
	}
	return (1);
}

void	lexer_eof_skip_whitespace(t_sh *shell, t_lexer *lexer)
{
	while (*lexer->cursor && ft_isspace(*lexer->cursor) && shell)
		lexer->cursor++;
}

void	lexer_eof_skip_comment(t_sh *shell, t_lexer *lexer)
{
	if (shell && *lexer->cursor == '#')
	{
		while (*lexer->cursor)
			lexer->cursor++;
	}
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
	if (!shell->lexer.tokens && !shell->lexer.token.value)
		return (AST_NULL);
	while (shell->lexer.tokens[i])
		i++;
	type = parse_get_type(shell->lexer.tokens[i - 1]);
	return (type);
}

void	sub_last_token(t_sh *shell, t_lexer *lexer)
{
	int		i;
	int		last_type;
	char	*token;
	char	**ntoks;

	i = 0;
	token = NULL;
	ntoks = lexer->tokens;
	last_type = lex_eof_get_last_type(shell);
	if (last_type > 1)
		string_array_push(&shell->lexer.tokens, ntoks[i++]);
	else if (shell->lexer.token.value)
		token = ft_strjoin(shell->lexer.token.value, ntoks[i++]);
	else if (shell->lexer.entry_state == 0)
		token = ft_strjoin(shell->line, ntoks[i++]);
	if (token)
		string_array_push(&shell->lexer.tokens, token);
	while (ntoks && ntoks[i])
		string_array_push(&shell->lexer.tokens, ntoks[i++]);
}
