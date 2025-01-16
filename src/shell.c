/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:21:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/16 11:45:23 by aseite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_init(t_sh *shell)
{
	ft_memset(shell, 0, sizeof(*shell));
	shell->name = "minishell";
	shell->pipe.in = STDIN_FILENO;
	shell->pipe.out = STDOUT_FILENO;
	printf("Hello<n");
}

static void	print_token(void *token)
{
	printf("%s\n", (char *)token);
}

void	shell_exec(t_sh *shell)
{
	shell->is_interactive = isatty(shell->pipe.in);
	errno = false;
	shell->is_running = true;
	while (shell->is_running)
	{
		input_read(shell);
		printf("READED: %s\n", shell->line);
		if (shell->line)
			input_parse(shell);
		printf("TOKENS:\n");
		ft_lstiter(shell->tokens, print_token);
		shell->is_running = false;
	}
}

void	shell_exit(t_sh *shell)
{
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	if (!shell->is_interactive && shell->pipe.in != -1)
		close(shell->pipe.in);
	if (!errno)
		exit(0);
	perror(shell->name);
	exit(1);
}
