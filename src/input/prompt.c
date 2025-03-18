/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:07:25 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/18 06:36:00 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_cat_or_grep(char *line)
{
	char	*iscat;
	char	*isgrep;

	iscat = ft_strchrstr(line, "cat");
	isgrep = ft_strchrstr(line, "grep");
	if (iscat || (isgrep && ft_strlen(isgrep) >= 6))
		return (true);
	return (false);
}

static void	add(t_sh *shell, char *msg, char *color)
{
	t_string	*prompt;

	if (!msg)
		return ;
	prompt = &shell->prompt;
	if (!prompt->value)
		return ;
	if (!color)
	{
		string_push_str(prompt, msg);
		return ;
	}
	string_push_str(prompt, "\033[");
	string_push_str(prompt, color);
	string_push_str(prompt, "m");
	string_push_str(prompt, msg);
	string_push_str(prompt, "\033[0m");
	return ;
}

void	shell_update_prompt(t_sh *shell)
{
	char	*base_color;
	char	cwd[1024];

	string_free(&shell->prompt);
	string_push_str(&shell->prompt, "");
	if (g_signal.is_sigint && shell->line && is_cat_or_grep(shell->line))
		g_signal.is_sigint = false;
	if (shell->exit_status)
		base_color = PROMPT_RED;
	else
		base_color = PROMPT_GREEN;
	add(shell, "╭─(", base_color);
	add(shell, env_get(shell, "LOGNAME"), PROMPT_BLUE);
	add(shell, "@", PROMPT_BLUE);
	add(shell, env_get(shell, "HOSTNAME"), PROMPT_BLUE);
	add(shell, ")─[", base_color);
	getcwd(cwd, 1024);
	add(shell, cwd, NULL);
	add(shell, "]", base_color);
	add(shell, "\n", NULL);
	add(shell, "╰─", base_color);
	add(shell, "$ ", PROMPT_BLUE);
}
