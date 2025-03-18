/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:10:44 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/18 15:18:38 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat_arr(char **arr)
{
	int		len;
	char	*cat;
	char	**_arr;
	char	*cursor;

	len = 0;
	_arr = arr;
	while (*_arr)
		len += ft_strlen(*(_arr++));
	cat = ft_calloc(len + 1, 1);
	if (!cat)
		return (NULL);
	_arr = arr;
	cursor = cat;
	while (*_arr)
		cursor = ft_stradd(*(_arr++), cursor, cat + len + 1);
	*cursor = '\0';
	return (cat);
}
