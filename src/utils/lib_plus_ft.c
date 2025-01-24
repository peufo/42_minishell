#include "minishell.h"

int 	ft_isalphanum(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	if (c <= 'z' && c >= 'a')
		return (1);
	if (c <= 'Z' && c >= 'A')
		return (1);
	return (0);
}