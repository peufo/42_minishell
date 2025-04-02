/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 05:26:28 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/02 11:08:18 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;
	
	len = strnlen(s, n);
	dup = malloc(len + 1);
	if (!dup)
	    return (NULL);
	ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}

static bool	get_code_fragment(char **end, bool *dq, bool *sq)
{
	if (!end || !(*end) || !(**end))
	    return (false);
	if (*dq || *sq)
		(*end)++;
	while (**end)
	{
	    if (*dq && **end == '"')
	        return (false);
	    if (*sq && **end == '\'')
	        return (false);
	    if (!(*dq) && !(*sq) && (ft_isspace(**end)
			|| **end == '\'' || **end == '"'))
	        return (false);
	    (*end)++;
	}
	return (true);
}

static char	*extract_code(char **line, bool dq, bool sq)
{
	char	*start;
	char	*end;
	size_t	len;
	char	*newcode;
	char	*tmp;	

	start = *line;
	end = start;
	len = ft_strlen(*line);
	newcode = ft_calloc(len + 1, 1);
	if (!newcode)
	    return (NULL);
	while (*start && !isspace(*start))
	{
	    check_quotes(*start, &dq, &sq);
	    if (dq || sq)
	        start++;
	    while (get_code_fragment(&end, &dq, &sq))
			continue ;
	    tmp = ft_strndup(start, end - start);
	    ft_strlcat(newcode, tmp, len + 1);
	    free(tmp);
	    start = end;
	}
	printf("Newcode is : %s\n", newcode);
	printf("Total line : %s\n", *line);
	return newcode;
}

static char	*catch_the_redir_code(char *line)
{
	char *tmp;
	
	tmp = ft_strchrstr(line, "<<");
	if (!tmp)
	    return (NULL);
	tmp += 2;
	while (isspace(*tmp))
	    tmp++;
	return (extract_code(&tmp, false, false));
}

void	get_all_codes(t_input *input, char *cursor)
{
	int		i;
	char	*tmp;
	char	*buf;

	i = 0;
	if (!cursor)
		return ;
	buf = ft_strchrstr(cursor, "<<");
	while (buf && i < input->nb_redir)
	{
		input->redir_code[i++] = catch_the_redir_code(buf);
		while (*buf == '<' || ft_isspace(*buf))
			buf++;
		while (ft_isalnum(*buf))
			buf++;
		tmp = ft_strchrstr(buf, "<<");
		buf = tmp;
	}
}
