/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:01:31 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/04 23:26:41 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_ARRAY_H
# define STRING_ARRAY_H
# include <unistd.h>
# include <stdbool.h>
# include "libft.h"

int		string_array_len(char **arr);
char	**string_array_dup(char **arr);
void	string_array_free(char ***arr);
void	string_array_push(char ***arr, char *str);
void	string_array_delete(char **arr, char *str);
char	**string_array_find(
			char **arr,
			char *pattern,
			bool (*match)(char *, char *)
			);
char	**string_array_find_start_with(char **arr, char *pattern);

#endif
