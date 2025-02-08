#include "minishell.h"

t_ast	*parse_handle_script(char **toks, int len, t_sh *shell)
{
	return (parse_handle_subshell(toks, len, shell));
}