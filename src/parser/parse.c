/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:24:16 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/04 15:35:31 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_free(t_sh *shell)
{
	(void)shell;
}

static void	pars_process_tokens(t_ast *ast, t_sh *shell)
{
	int	index;

	if (!ast)
		return ;
	index = 0;
	while (ast->args != NULL && index < 3)
	{
		pars_find_next_operator(ast);
		pars_context_type(ast);
		pars_parse_command(ast);
		debug_arr(shell, (char *[]){
			"ast_type -> [",
			ft_itoa(ast->type),
			"]\nfor token indexed at -> [",
			ft_itoa(index),
			"]\n",
			NULL
		});
		index++;
	}
}

static void	debug_tokens(t_sh *shell)
{
	t_list	*current;
	t_token	*token;

	current = shell->lexer.tokens;
	debug(shell, "\nTokens received:\n");
	while (current)
	{
		token = (t_token *)current->content;
		if (token && token->value)
		{
			debug_arr(shell, (char *[]){
				"[",
				token->type,
				"] -> ",
				token->value,
				"\n",
				NULL
			});
		}
		else
			printf("- [NULL or invalid token]\n");
		current = current->next;
	}
}

void	parse(t_sh *shell)
{
	if (!shell || !shell->lexer.tokens)
		return (throw_error("No tokens received", __FILE__, __LINE__));
	debug_tokens(shell);
	shell->ast.type = AST_COMMAND;
	shell->ast.args = shell->lexer.tokens;
	if (ft_lstsize(shell->ast.args) == 1)
		return ;
	pars_process_tokens(&shell->ast, shell);
}
