/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 00:30:08 by jvoisard          #+#    #+#             */
/*   Updated: 2024/10/08 16:32:49 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_digit_pos(int n, int fd)
{
	char	digit;

	if (!n)
		return ;
	digit = (n % 10) + '0';
	put_digit_pos(n / 10, fd);
	write(fd, &digit, 1);
}

static void	put_digit_neg(int n, int fd)
{
	char	digit;

	if (!n)
		return ;
	digit = -(n % 10) + '0';
	put_digit_neg(n / 10, fd);
	write(fd, &digit, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n > 0)
	{
		put_digit_pos(n, fd);
		return ;
	}
	write(fd, "-", 1);
	put_digit_neg(n, fd);
}
