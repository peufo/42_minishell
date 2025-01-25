#include "minishell.h"

static int	process_gate(t_sh *shell)
{
	if (*shell->lexer.cursor == '&')
	{
		*shell->lexer.cursor += 1;
		if (*shell->lexer.cursor == '&')
			return (AND_GATE);
		else
			return (BULLSHIT);
	}
	else if (*shell->lexer.cursor == '|')
	{
		*shell->lexer.cursor += 1;
		if (*shell->lexer.cursor == '|')
			return (OR_GATE);
		else if (*shell->lexer.cursor == ' ')
			return (PIPE);
	}
	return (BULLSHIT);
}

static int	process_direction(t_sh *shell)
{
	if (*shell->lexer.cursor == '>')
	{
		*shell->lexer.cursor += 1;
		if (*shell->lexer.cursor == '>')
			return (RIGHT_DRDIR);
		else if (*shell->lexer.cursor == ' ')
			return (RIGHT_RDIR);
		else
			return (BULLSHIT);
	}
	if (*shell->lexer.cursor == '<')
	{
		*shell->lexer.cursor += 1;
		if (*shell->lexer.cursor == '>')
			return (LEFT_DRDIR);
		else if (*shell->lexer.cursor == ' ')
			return (LEFT_RDIR);
		else
			return (BULLSHIT);
	}
	return (BULLSHIT);
}

int 	get_char_state(t_sh *shell)
{
	if (*shell->lexer.cursor == '\'')
		return (check_errors(shell, '\''));
	if (*shell->lexer.cursor == '"')
		return (check_errors(shell, '"'));
	if (*shell->lexer.cursor == '$')
		return (L_VAR);
	if (*shell->lexer.cursor == '\'')
		return (L_DVAR);
	if (*shell->lexer.cursor == '#')
		return (L_IGNORE);
	if (*shell->lexer.cursor == '(')
		return (L_PAR_OPEN);
	if (*shell->lexer.cursor == ')')
		return (L_PAR_CLOSE);
	if (*shell->lexer.cursor == '<' || *shell->lexer.cursor == '>')
		return (process_direction(shell));
	if (*shell->lexer.cursor == '|')
		return (process_gate(shell));
	return (-1);
}
