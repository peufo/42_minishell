/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:01:31 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/13 22:33:55 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_ARRAY_H
# define STRING_ARRAY_H
# include <unistd.h>
# include <stdbool.h>
# include "libft.h"

int		string_array_len(char **arr);
char	**string_array_dup(char **arr);
char	**string_array_slice(char **from, char **to);
void	string_array_free(char ***arr);
void	string_array_push(char ***arr, char *str);
void	string_array_unshift(char ***arr, char *str);
void	string_array_delete(char **arr, char *str);
char	**string_array_find_start_with(char **arr, char *pattern);
char	**string_array_find_match(char **arr, char *pattern);
char	**string_array_find_last_start_with(char **arr, char *pattern);
char	**string_array_find_last_match(char **arr, char *pattern);

bool	string_match(char *pattern, char *str);
bool	string_match_start_with(char *pattern, char *str);

#endif
