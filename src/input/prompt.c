/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:07:25 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/14 12:28:25 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add(t_sh *shell, char *msg, char *color)
{
	t_string	*prompt;

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
	shell->prompt.value = ft_strdup("MINISHELL>");
	return ;
	string_free(&shell->prompt);
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
	return ;
}
