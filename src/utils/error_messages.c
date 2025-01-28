#include "minishell.h"

static void	message5(int error)
{
	if (error == BAD_PARENTHESIS)
		ft_putstr_fd("\n", 1);
	else
		ft_putstr_fd("Unknown Error\n", 1);
}

static void	message4(int error)
{
	if (error == BAD_PARENTHESIS)
		ft_putstr_fd("\n", 1);
	else
		message5(error);
}

static void	message3(int error)
{
	if (error == BAD_PARENTHESIS)
		ft_putstr_fd("\n", 1);
	else
		message4(error);
}

static void	message2(int error)
{
	if (error == BAD_PARENTHESIS)
		ft_putstr_fd("Token '(' incomplete\n", 1);
	else
		message3(error);
}

void	message(int error, int function)
{
	ft_putstr_fd("\n\n", 1);
	ft_putstr_fd("/------------------------------------\\", 1);
	ft_putstr_fd("\n/************GOT AN ERROR !***********\\\n", 1);
	ft_putstr_fd("Error code : ", 1);
	ft_putnbr_fd(error, 1);
	ft_putstr_fd("\nERROR DESCRIPTION : ", 1);
	if (error == BAD_PARENTHESIS)
		ft_putstr_fd("Token '(' or ')' incomplete\n", 1);
	else
		message2(error);
	ft_putstr_fd("Error origin in function : \n", 1);
	track_origin(function);
	ft_putstr_fd("\\************END OF MESSAGE***********/\n", 1);
	ft_putstr_fd("\\-------------------------------------/\n", 1);
	ft_putstr_fd("\n\n", 1);
}
