/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:07:25 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/31 13:12:31 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add(t_sh *shell, char *msg)
{
	t_string	*prompt;

	if (!msg)
		return ;
	prompt = &shell->prompt;
	if (!prompt->value)
		return ;
	string_push_str(prompt, msg);
}

void	shell_update_prompt(t_sh *shell)
{
	char	cwd[1024];

	string_free(&shell->prompt);
	string_push_str(&shell->prompt, "");
	add(shell, "╭─(");
	add(shell, env_get(shell, "LOGNAME"));
	add(shell, "@");
	add(shell, env_get(shell, "HOSTNAME"));
	add(shell, ")─[");
	getcwd(cwd, 1024);
	add(shell, cwd);
	add(shell, "]");
	add(shell, "\n");
	add(shell, "╰─");
	add(shell, "$ ");
}
