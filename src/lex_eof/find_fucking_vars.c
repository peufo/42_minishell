/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_fucking_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:44:30 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/02 14:10:34 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_vars(char *line)
{
	int		count;
	char	*ptr;

	ptr = line;
	count = 0;
	ptr = ft_strchr(ptr, '$');
	while (ptr != NULL)
	{
		count++;
		ptr++;
		ptr = ft_strchr(ptr, '$');
	}
	return (count);
}

static char	*extract_varname(char *ptr)
{
	char	*start;
	char	*end;
	size_t	len;
	char	*varname;	

	start = ptr + 1;
	end = start;
	while (*end && ((*end >= 'A' && *end <= 'Z')
			|| (*end >= 'a' && *end <= 'z') || (*end >= '0' && *end <= '9')
			|| *end == '_'))
		end++;
	len = end - start;
	varname = (char *)malloc(len + 1);
	if (varname)
	{
		strncpy(varname, start, len);
		varname[len] = '\0';
	}
	return (varname);
}

void	find_vars_in_line(char **line, char ***vars)
{
	int		var_count;
	char	*ptr;
	int		i;	

	i = 0;
	ptr = *line;
	var_count = count_vars(*line);
	*vars = (char **)malloc((var_count + 1) * sizeof(char *));
	if (!*vars)
		return ;
	ptr = ft_strchr(ptr, '$');
	while (ptr != NULL)
	{
		(*vars)[i++] = extract_varname(ptr);
		ptr++;
		ptr = ft_strchr(ptr, '$');
	}
	(*vars)[i] = NULL;
}

static void	replace_var_in_line(char **placeholder, char **varname,
		char **newline, char **value)
{
	char	*ptr;
	size_t	prefix_len;
	size_t	suffix_len;
	char	*new_str;

	custom_sprintf(*placeholder, "$%s", *varname, ft_strlen(*varname));
	ptr = *newline;
	ptr = ft_strnstr(ptr, *placeholder, ft_strlen(ptr));
	while (ptr != NULL)
	{
		prefix_len = ptr - *newline;
		suffix_len = ft_strlen(ptr + ft_strlen(*placeholder));
		new_str = malloc(prefix_len + ft_strlen(*value) + suffix_len + 1);
		ft_memcpy(new_str, *newline, prefix_len);
		ft_memcpy(new_str + prefix_len, *value, ft_strlen(*value));
		ft_memcpy(new_str + prefix_len + ft_strlen(*value),
			ptr + ft_strlen(*placeholder), suffix_len + 1);
		free(*newline);
		*newline = new_str;
		ptr = *newline + prefix_len + ft_strlen(*value);
		ptr = ft_strnstr(ptr, *placeholder, ft_strlen(ptr));
	}
}

void	expand_vars_in_line(t_sh *shell, char **line, char ***vars)
{
	char	*placeholder;
	char	*new_line;
	char	*varname;
	char	*value;
	int		i;

	i = 0;
	new_line = ft_strdup(*line);
	while ((*vars)[i])
	{
		varname = (*vars)[i];
		value = env_get(shell, varname);
		if (value)
		{
			placeholder = (char *)malloc(strlen(varname) + 2);
			if (placeholder)
				replace_var_in_line(&placeholder, &varname, &new_line, &value);
		}
		free(varname);
		i++;
	}
	free(*vars);
	free(*line);
	*line = new_line;
}
