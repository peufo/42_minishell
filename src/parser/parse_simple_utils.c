/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 03:50:30 by dyodlm            #+#    #+#             */
/*   Updated: 2025/02/11 04:38:05 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*pars_new_ast(t_ast ast)
{
	t_ast	*node;

	node = malloc(sizeof(ast));
	if (!node)
		return (throw_error("malloc :", __FILE__, __LINE__), NULL);
	else
		*node = ast;
	return (node);
}

