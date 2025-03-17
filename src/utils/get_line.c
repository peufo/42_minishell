/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:18:09 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/17 17:49:37 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line(int fd)
{
	ssize_t bytes_read;
	char	buffer[256];
	char	*stack = NULL;

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
