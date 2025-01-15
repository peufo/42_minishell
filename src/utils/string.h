/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:22:34 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/15 19:48:09 by jvoisard         ###   ########.fr       */
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

t_string_result	string_push(t_string *string, char c);

#endif