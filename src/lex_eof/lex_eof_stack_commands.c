/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_stack_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:51:49 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/23 10:54:37 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stack_to_buffer(char **buffer, char *line)
{
	char	*tmp;
	size_t	tlen;

	if (!line)
		return ;
	tlen = ft_strlen(line) + 2;
	if (buffer && *buffer)
		tlen += ft_strlen(*buffer);
	tmp = ft_calloc(1, tlen + 1);
	if (!tmp)
		return ;
	if (buffer && *buffer)
	{
		ft_strlcat(tmp, ft_strdup(*buffer), tlen + 1);
		ft_strlcat(tmp, ft_strdup("\n"), tlen + 1);
	}
	ft_strlcat(tmp, line, tlen + 1);
	free(*buffer);
	*buffer = tmp;
	printf("buffer is : %s\n", *buffer);
}

void	stack_new_input(char **buffer, t_lexer *lex,
		char ***new_tokens, char *line)
{
	int	i;

	i = 0;
	if (!*new_tokens)
	{
		*new_tokens = ft_calloc(1, sizeof(char *));
		if (!*new_tokens)
			return ;
	}
	while (lex->tokens && lex->tokens[i])
		string_array_push(new_tokens, lex->tokens[i++]);
	printf("Nb of tokens pushed into new tab is : %d\n", i);
	stack_to_buffer(buffer, line);
}
