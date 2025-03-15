/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:07:25 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/15 15:09:59 by jvoisard         ###   ########.fr       */
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

	if (shell->prompt.value)
		free(shell->prompt.value);
	if (g_signal.is_sigint && shell->line && is_cat_or_grep(shell->line))
		shell->prompt.value = ft_strdup("");
	else
		shell->prompt.value = ft_strdup("MINISHELL>");
	g_signal.is_sigint = false;
	return ;
	if (shell->exit_status)
		base_color = PROMPT_RED;
	else
		base_color = PROMPT_GREEN;
	add(shell, "╭─(", base_color);
	add(shell, env_get(shell, "LOGNAME"), PROMPT_BLUE);
	add(shell, "@", PROMPT_BLUE);
	add(shell, env_get(shell, "HOSTNAME"), PROMPT_BLUE);
	add(shell, ")─[", base_color);
	add(shell, env_get(shell, "PWD"), PROMPT_YELLOW);
	add(shell, "]", base_color);
	add(shell, "\n", NULL);
	add(shell, "╰─", base_color);
	add(shell, "$ ", PROMPT_BLUE);
}
