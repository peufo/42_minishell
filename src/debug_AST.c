/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_AST.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:27:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/17 07:01:27 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_ast(t_sh *shell, t_ast *ast, int depth);

static void	type_to_str(t_sh *shell, int type)
{
	if (type == 0)
		debug(shell, " AST_SCRIPT");
	if (type == 1)
		debug(shell, " AST_COMMAND");
	if (type == 2)
		debug(shell, " AST_PIPELINE");
	if (type == 3)
		debug(shell, " AST_LOGICAL");
	if (type == 4)
		debug(shell, " AST_REDIRECT");
	if (type == 5)
		debug(shell, " AST_SUBSHELL");
	if (type == 6)
		debug(shell, " AST_END");
}

static void	op_to_str(t_sh *shell, int type)
{
	if (type == AST_OP_AND)
		debug(shell, "AND OPERATOR [&&]");
	else if (type == AST_OP_OR)
		debug(shell, "OR OPERATOR [||]");
	else if (type == AST_OP_GREAT)
		debug(shell, "SIMPLE REDIR [>]");
	else if (type == AST_OP_DGREAT)
		debug(shell, "DOUBLE REDIR [>>]");
	else if (type == AST_OP_LESS)
		debug(shell, "SIMPLE REDIR [<]");
	else if (type == AST_OP_DLESS)
		debug(shell, "DOUBLE REDIR [<<]");
	else
		debug(shell, "OPERATOR NULL");
}

static void	handle_recursion(t_sh *shell, t_ast *node, int depth, char *side)
{
	int	i;

	i = 0;
	while (i++ < depth + 1)
		debug(shell, "	");
	debug_arr(shell, (char *[]){side, "\n", NULL});
	print_ast(shell, node, depth + 1);
}

static void	print_ast(t_sh *shell, t_ast *ast, int depth)
{
	t_utils	u;

	ft_bzero(&u, sizeof(t_utils));
	if (!ast)
		return ;
	while (u.i++ < depth)
		debug(shell, "  ");
	type_to_str(shell, ast->type);
	if (ast->args)
	{
		debug(shell, " ||==> Args: ");
		while (u.j < 2 && ast->args[u.j])
			debug_arr(shell, (char *[]){"arg: ", ast->args[u.j++], " ", NULL});
	}
	if (ast->op != AST_OP_NULL)
	{
		debug(shell, " ||===> Operator:");
		op_to_str(shell, ast->op);
	}
	debug(shell, "\n");
	if (ast->left)
		handle_recursion(shell, ast->left, depth, "Left");
	if (ast->right)
		handle_recursion(shell, ast->right, depth, "Right");
}

void	debug_ast(t_sh *shell)
{
	debug(shell, "\n\nPRINTING AST\n");
	debug(shell, "AST Structure:\n");
	print_ast(shell, shell->ast, 0);
}
