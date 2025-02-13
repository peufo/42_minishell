/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_script.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:10:12 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/13 17:49:41 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static bool	parse_get_starter(char *str, char *start)
{
    return (strncmp(str, start, strlen(start)) == 0);
}*/
/*
static t_ast	*parse_handle_subscript(char **toks, t_sh *shell)
{
	t_ast	*ast;
	int		len;

	debug(shell, "into hande subscript \n");
	ast = parse_init_ast();world
	len = parse_toks_len(toks);
	if (len > 0 && parse_get_starter(toks[0], "("))
	{
		ast->type = AST_SUBSHELL;
		ast->left = parse_handle_script(toks + 1, shell);
		if (parse_get_starter(toks[len - 1], ")"))
			toks[len - 1] = NULL;
    }
    return (ast);
}*/

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
	len = parse_toks_len(toks);
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

/*
t_ast	*parse_handle_script(char **toks, t_sh *shell)
{
	t_ast		*ast;
	int			len;
	int			type;
	static int	i = 0;

	len = parse_toks_len(toks);
	ast = parse_init_ast();
	while (i < len)
	{
		i++;
		type = parse_get_type(toks[i - 1]);
		if (type != AST_COMMAND)
		{
			ast->type = type;
			ast->op = parse_get_op(toks[i - 1]);
			ast->left = parse_handle_script(toks + i, shell);
			ast->right = parse_handle_script(toks + i + 1, shell);
			break ; 
		}
		else
		{
			ast->type = AST_COMMAND;
			ast->args = parse_word_content(shell, toks[i - 1]);
		}
	}
	return (ast);
}*/
