/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:21:29 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/16 16:17:04 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_init(t_sh *shell)
{
	ft_memset(shell, 0, sizeof(*shell));
	shell->name = "minishell";
	shell->pipe.in = STDIN_FILENO;
	shell->pipe.out = STDOUT_FILENO;
}

static void	print_token(void *token)
{
	static int	i;

	printf("%d: %s\n", i++, (char *)token);
}

void	shell_exec(t_sh *shell)
{
	shell->is_interactive = isatty(shell->pipe.in);
	errno = false;
	shell->is_running = true;
	while (shell->is_running)
	{
		input_read(shell);
		printf("\nLINE: %s\n", shell->line);
		if (shell->line)
			input_parse(shell);
		printf("TOKENS:\n");
		ft_lstiter(shell->tokens, print_token);
		shell->is_running = false;
	}
	shell_exit(shell);
}

void	shell_exit(t_sh *shell)
{
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	ft_lstclear(&shell->tokens, free);
	if (!shell->is_interactive && shell->pipe.in != -1)
		close(shell->pipe.in);
	printf("\n[ CLEAN EXIT OK ]\n");
	if (!errno)
		exit(0);
	perror(shell->name);
	exit(1);
}
