/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_script.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:10:12 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/16 09:03:45 by dyodlm           ###   ########.fr       */
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
	t_utils		u;
	t_ast		*ast;
	t_ast		*new;
	t_ast		*ref;

	ast = NULL;
	ref = NULL;
	ft_bzero(&u, sizeof(t_utils));
	u.x = string_array_len(toks);
	while (u.i < u.x)
	{
		new = parse_init_ast();
		new->type = parse_get_type(toks[u.i]);
		if (new->type == AST_COMMAND)
			new->args = parse_word_content(shell, toks[u.i]);
		else if (new->type != AST_END)
			new->op = parse_get_op(toks[u.i]);
		if (!ast)
			ast = new;
		else
			swap_alignment(&new, &ast, &ref);
		ref = new;
		u.i++;
	}
	return (string_array_free(&toks), ast);
}
