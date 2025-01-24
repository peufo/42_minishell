#include "minishell.h"

static void		message5(int error)
{
	if (error == BAD_PARENTHESIS)
		ft_putstr_fd("\n", 1);
	else
		ft_putstr_fd("Unknown Error\n", 1);
}

static void		message4(int error)
{
	if (error == BAD_PARENTHESIS)
		ft_putstr_fd("\n", 1);
	else
		message5(error);
}

static void		message3(int error)
{
	if (error == BAD_PARENTHESIS)
		ft_putstr_fd("\n", 1);
	else
		message4(error);
}

static void		message2(int error)
{
	if (error == BAD_PARENTHESIS)
		ft_putstr_fd("Token '(' incomplete\n", 1);
	else
		message3(error);
}

void	message(int error, int function)
{
	if (error == BAD_PARENTHESIS)
		ft_putstr_fd("Token '(' or ')' incomplete\n", 1);
	else
		message2(error);
	ft_putstr_fd("Error origin in function :", 1);
	track_origin(function);
}
