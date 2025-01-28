#include "minishell.h"

/*I don't know exactly how to do that*/
pid_t	get_the_pid(char *process)
{
	if (process != NULL)
		return (getpid());
	else
		return (0);
}
/*
static char	*extract_varname(t_lexer *lexer)
{
	char	*start;
	size_t	len;

	start = lexer->cursor;
	if (!lexer || !start)
		return (NULL);
	len = 0;
	while ((start[len] && ft_isalnum(start[len])) || start[len] == '_')
		len++;
	return (ft_substr(start, 0, len));
}

void	tokenise_quote(t_lexer *lexer)
{
	t_list	*start;
	char	*index;
	char	*token;

	if (!lexer || !lexer->starters)
	{
		message(NULL_STRING, TOKENISE_QUOTES);
		return ;
	}
	start = ft_lstlast(lexer->starters);
	if (!start || !start->content)
	{
		message(NO_STARTER, TOKENISE_QUOTES);
		return ;
	}
	index = (char *)start->content;
	token = ft_substr(index, 0, lexer->cursor - index);
	if (!token)
	{
		message(TOKEN_PROBLEM, TOKENISE_QUOTES);
		return ;
	}
	lexer_add_token(lexer, L_WORD, token);
	ft_lstdelone(start, free);
}

void	tokenise_variable(t_lexer *lexer)
{
	char	*varname;

	if (!lexer)
		return ;
	varname = extract_varname(lexer);
	if (varname)
		lexer_add_token(lexer, L_VAR, varname);
}
*/