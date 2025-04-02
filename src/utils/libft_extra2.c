/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extra2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:00:09 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/02 13:47:26 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_redir(char *cursor)
{
	if (cursor && cursor[0] == '<' && cursor[1] == '<')
		return (true);
	return (false);
}

char	*ft_strchrstr(const char *str, char *to_find)
{
	char	*cursor;
	size_t	j;
	size_t	len;

	len = ft_strlen(to_find);
	cursor = (char *)str;
	while (cursor && *cursor)
	{
		j = 0;
		while (to_find[j] && cursor[j] == to_find[j])
			j++;
		if (j >= len)
			return (cursor);
		cursor++;
	}
	return (NULL);
}

void	ft_strcpy(char *s1, const char *s2)
{
	if (!s1 || !s2)
		return ;
	while (s2 && *s2)
	{
		*s1 = *s2;
		s2++;
		s1++;
	}
	*s1 = '\0';
}

static void	action(char **dest, const char **str_arg)
{
	ft_strcpy(*dest, *str_arg);
	*dest += ft_strlen(*str_arg);
}

void	custom_sprintf(
	char *buffer,
	const char *format,
	const char *str_arg,
	int int_arg
	)
{
	char		int_buf[12];
	int			int_len;
	const char	*src;
	char		*dest;	

	src = format;
	dest = buffer;
	int_len = int_arg;
	while (*src)
	{
		if (*src == '%' && (*(src + 1) == 's' || *(src + 1) == 'd'))
		{
			if (*(src + 1) == 's')
				action(&dest, &str_arg);
			else if (*(src + 1) == 'd')
			{
				ft_strcpy(dest, int_buf);
				dest += int_len;
			}
			src += 2;
		}
		else
			*dest++ = *src++;
	}
	*dest = '\0';
}
