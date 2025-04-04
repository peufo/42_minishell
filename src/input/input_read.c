/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:36:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/04 15:27:37 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prompt_add(t_sh *shell, char *msg)
{
	t_string	*prompt;

	if (!msg)
		return ;
	prompt = &shell->prompt;
	if (!prompt->value)
		return ;
	string_push_str(prompt, msg);
}

static void	shell_update_prompt(t_sh *shell)
{
	char	cwd[1024];

	string_free(&shell->prompt);
	string_push_str(&shell->prompt, "");
	prompt_add(shell, "╭─(");
	prompt_add(shell, env_get(shell, "LOGNAME"));
	prompt_add(shell, "@");
	prompt_add(shell, env_get(shell, "HOSTNAME"));
	prompt_add(shell, ")─[");
	getcwd(cwd, 1024);
	prompt_add(shell, cwd);
	prompt_add(shell, "]");
	prompt_add(shell, "\n");
	prompt_add(shell, "╰─");
	prompt_add(shell, "$ ");
}

static void	reset_line(t_sh	*shell)
{
	if (!shell->line)
		return ;
	free(shell->line);
	shell->line = NULL;
}

void	input_read(t_sh	*shell)
{
	reset_line(shell);
	if (shell->is_interactive)
	{
		shell_update_prompt(shell);
		shell->line = readline(shell->prompt.value);
		errno = false;
		if (!ft_isempty(shell->line))
			add_history(shell->line);
	}
	else
		shell->line = get_next_line(shell->fd_in);
	if (errno)
		shell_exit(shell);
}
