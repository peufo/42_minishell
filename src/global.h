/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:40:30 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/25 17:41:52 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

typedef struct s_signal
{
	bool	is_sigint;
	bool	is_sigquit;
	int		exit_status;
}	t_signal;

extern t_signal	g_signal;

#endif
