#include "minishell.h"

static void		message5(int sig)
{
	if (sig == BAD_PARENTHESIS)
		ft_putstr_fd("\n", 1);
	else
		ft_putstr_fd("Unknown Error\n");
}

static void		message4(int sig)
{
	if (sig == BAD_PARENTHESIS)
		ft_putstr_fd("\n", 1);
	else
		message5(sig);
}

static void		message3(int sig)
{
	if (sig == BAD_PARENTHESIS)
		ft_putstr_fd("\n", 1);
	else
		message4(sig);
}

static void		message2(int sig)
{
	if (sig == BAD_PARENTHESIS)
		ft_putstr_fd("Token '(' incomplete\n", 1);
	else
		message3(sig);
}

void	message(int sig)
{
	if (sig == BAD_PARENTHESIS)
		ft_putstr_fd("Token '(' or ')' incomplete\n", 1);
	else
		message2(sig);
}
