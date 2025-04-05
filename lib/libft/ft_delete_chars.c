/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:11:34 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/05 14:12:41 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_delete_chars(char *from, char *to)
{
	if (!to)
	{
		to = from;
		while (*to)
			to++;
	}
	while (*to)
		*(from++) = *(to++);
	while (from <= to)
		*(from++) = '\0';
}
