#include "minishell.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_isalphanum(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	if (c <= 'z' && c >= 'a')
		return (1);
	if (c <= 'Z' && c >= 'A')
		return (1);
	return (0);
}

char	*ft_strndup(const char *str, size_t n)
{
	char	*result;
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (str[len] && len < n)
		len++;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = str[i];
		i++;
	}
	result[len] = '\0';
	return (result);
}
