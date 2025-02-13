/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_script.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:10:12 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/13 18:20:25 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_alignment(t_ast	**new_node, t_ast **original, t_ast **ref)
{
	if ((*new_node)->type == AST_LOGICAL)
	{
		(*new_node)->left = *original;
		*original = *new_node;
	}
	else
		(*ref)->right = *new_node;
}

t_ast	*parse_handle_script(char **toks, t_sh *shell)
{
	static int		i;
	int				len;
	t_ast			*ast;
	t_ast			*new;
	t_ast			*ref;

	ast = NULL;
	ref = NULL;
	len = string_array_len(toks);
	while (i < len)
	{
		new = parse_init_ast();
		new->type = parse_get_type(toks[i]);
		if (new->type == AST_COMMAND)
			new->args = parse_word_content(shell, toks[i]);
		else if (new->type == AST_LOGICAL)
			new->op = parse_get_op(toks[i]);
		if (!ast)
			ast = new;
		else
			swap_alignment(&new, &ast, &ref);
		ref = new;
		i++;
	}
	return (ast);
}
