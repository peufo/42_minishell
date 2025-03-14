/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_startwith.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:55:35 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/14 19:55:50 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_startwith(char *str, char *start)
{
	while (*start && *str)
		if (*(start++) != *(str++))
			return (0);
	if (*start)
		return (0);
	return (1);
}
