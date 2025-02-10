/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_extra2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:56:14 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/10 14:56:16 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2dtab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (throw_error("Nothing to free in :", __FILE__, __LINE__));
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}
