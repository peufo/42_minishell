#include "minishell.h"

void	look_for_special_commands(t_sh *shell)
{
	char	*line;

	line = shell->lexer.cursor;
	if (!line)
		return ;
	else if (!ft_strncmp(line, "exitshell", 9))
		shell_exit(shell);
}
