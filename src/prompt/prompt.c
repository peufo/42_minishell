/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:36:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/14 13:42:29 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char *input;

	input = readline("minishell>");
	ft_putstr("Do something with ");
	ft_putstr(input);
	ft_putstr("\n");
	free(input);
}