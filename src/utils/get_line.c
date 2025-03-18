/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:18:09 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/17 19:03:38 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_safely(char **newline,
						char **line,
						char buffer[256],
						t_utils *u)
{
	buffer[u->i++] = **line;
	(*line)++;
	if (u->i == 255)
	{
		stack_to_buffer(newline, buffer);
		ft_bzero(&buffer, 256);
		u->i = 0;
		u->j += 255;
	}
}

/* u.i --> first step || u.j --> second step || u.x -->len	*/
static char	*get_newline(char *line, int step1, int step2)
{
	static char	buffer[256];
	char		*newline;
	t_utils		u;

	newline = NULL;
	ft_bzero(&u, sizeof(t_utils));
	ft_bzero(&buffer, 256);
	u.x = ft_strlen(line);
	while (*line && u.i + u.j < step1)
		copy_safely(&newline, &line, buffer, &u);
	while (*line && step1++ < step2)
		line++;
	while (*line && u.i + u.j < u.x)
		copy_safely(&newline, &line, buffer, &u);
	stack_to_buffer(&newline, buffer);
	return (newline);
}

void	ft_suppress(char *from, char *to, char **line)
{
	char	*newline;
	int		step1;
	int		step2;

	step1 = ft_strlen(*line) - ft_strlen(from);
	step2 = ft_strlen(*line) - ft_strlen(to);
	newline = get_newline(*line, step1, step2);
	free(*line);
	*line = newline;
}

char	*get_line(int fd)
{
	ssize_t	bytes_read;
	char	buffer[256];
	char	*stack;

	stack = NULL;
	while (1)
	{
		bytes_read = read(fd, buffer, sizeof(buffer) - 1);
		if (bytes_read == -1)
			return (free(stack), NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stack_to_buffer(&stack, buffer);
		if (ft_strchr(buffer, '\0') != NULL)
			break ;
	}
	return (stack);
}
