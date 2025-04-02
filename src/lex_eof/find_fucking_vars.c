/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_fucking_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:44:30 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/02 11:50:09 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_vars(char *line)
{
    int count;
    char *ptr;
	
	ptr = line;
	count = 0;
    while ((ptr = strchr(ptr, '$')) != NULL)
	{
        count++;
        ptr++;
    }
    return (count);
}

static char *extract_varname(char *ptr)
{
    char *start;
    char *end;
	size_t	len;
	char	*varname;

	start = ptr + 1;
	end = start;
    while (*end && ((*end >= 'A' && *end <= 'Z')
		|| (*end >= 'a' && *end <= 'z') || (*end >= '0' && *end <= '9')
		|| *end == '_')) {
        end++;
    }
    len = end - start;
    varname = (char *)malloc(len + 1);
    if (varname)
	{
        strncpy(varname, start, len);
        varname[len] = '\0';
    }
    return varname;
}

void find_vars_in_line(char **line, char ***vars)
{
    int var_count = count_vars(*line);
    *vars = (char **)malloc((var_count + 1) * sizeof(char *));
    if (!*vars) return;

    char *ptr = *line;
    int i = 0;
    while ((ptr = ft_strchr(ptr, '$')) != NULL) {
        (*vars)[i++] = extract_varname(ptr);
        ptr++;
    }
    (*vars)[i] = NULL;
}


void	expand_vars_in_line(t_sh *shell, char **line, char ***vars)
{
	char *new_line = strdup(*line);
	if (!new_line) return;

	for (int i = 0; (*vars)[i]; i++) {
		char *varname = (*vars)[i];
		char *value = env_get(shell, varname);
		if (value) {
			char *var_placeholder = (char *)malloc(strlen(varname) + 2);
			if (var_placeholder) {
				sprintf(var_placeholder, "$%s", varname);
				char *ptr = new_line;
				while ((ptr = strstr(ptr, var_placeholder)) != NULL) {
					size_t prefix_len = ptr - new_line;
					size_t suffix_len = strlen(ptr + strlen(var_placeholder));
					char *new_str = (char *)malloc(prefix_len + strlen(value) + suffix_len + 1);
					if (new_str) {
						strncpy(new_str, new_line, prefix_len);
						strcpy(new_str + prefix_len, value);
						strcpy(new_str + prefix_len + strlen(value), ptr + strlen(var_placeholder));
						free(new_line);
						new_line = new_str;
						ptr = new_line + prefix_len + strlen(value);
					}
				}
				free(var_placeholder);
			}
		}
		free(varname);
	}
	free(*vars);
	free(*line);
	*line = new_line;	
}
