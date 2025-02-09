#include "minishell.h"

void	free_2dtab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (throw_error("Nothing to free in :", __FILE__, __LINE__));
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}