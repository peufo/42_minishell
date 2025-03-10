/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_eof_checkers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:42:33 by dyodlm            #+#    #+#             */
/*   Updated: 2025/03/10 13:10:59 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Don't try to understand this shit. It's temporary debug */

int	get_the_fucking_line(t_sh *shell)
{
	if (shell->input->is_redir)
		shell->input->redir_line = readline("redir-mode > ");
	else
		shell->input->line = readline("> ");
	if (!shell->input->line && !shell->input->redir_line)
		shell_exit(shell);
	if (shell->input->line && is_empty_line(shell->input->line))
		shell->input->line = NULL;
	else
		return (1);
	if (shell->input->redir_line && is_empty_line(shell->input->redir_line))
		shell->input->redir_line = NULL;
	else
		return (1);
	if (!shell->input->line)
		shell->input->line = shell->input->redir_line;
	return (0);
}
