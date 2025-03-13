/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:22:34 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/13 21:27:33 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H
# define STRING_INITAL_LEN 64
# include <unistd.h>
# include "libft.h"

typedef enum e_string_result
{
	STRING_SUCCESS = 0,
	STRING_ERROR = 1
}	t_string_result;

typedef struct s_string
{
	char			*value;
	unsigned int	len;
}	t_string;

t_string_result	string_push_char(t_string *string, char c);
t_string_result	string_push_str(t_string *string, char *str);
void			string_free(t_string *string);
t_string_result	string_replace(
					t_string *string,
					char *start,
					char *end,
					char *with);

#endif