#include "minishell.h"

static int	process_gate(t_sh *shell)
{
	s;
}

static int	process_direction(t_sh *shell
{
	s;
}

int 	get_next_simple_state(t_sh *shell)
{
	if (*shell->lexer.cursor == "'")
		return (L_QUOTE);
	if (*shell->lexer.cursor == "'")
		return (L_DQUOTE);
	if (*shell->lexer.cursor == "'")
		return (L_VAR);
	if (*shell->lexer.cursor == "'")
		return (L_DVAR);
	if (*shell->lexer.cursor == "'")
		return (L_IGNORE);
	if (*shell->lexer.cursor == "'")
		return (L_PAR_OPEN);
	if (*shell->lexer.cursor == "'")
		return (L_PAR_CLOSE);
	if (*shell->lexer.cursor == '<' || *shell->lexer.cursor == '>')
		return (process_direction(shell));
	if (*shell->lexer.cursor == '|')
		return (process_gate(shell));
	return (-1);
}
