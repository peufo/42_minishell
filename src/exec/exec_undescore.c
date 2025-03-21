#include "minishell.h"

void	exec_update_underscore(t_ast *node)
{
	char	**tokens;
	char	*env_underscore;

	tokens = node->tokens;
	if (!tokens)
		return ;
	while (*tokens && *(tokens + 1))
		tokens++;
	env_underscore = ft_strcat("_=", *tokens);
	if (!env_underscore)
		shell_exit(node->shell);
	env_set(node->shell, "_", env_underscore);
}