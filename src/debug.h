/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:12:11 by jvoisard          #+#    #+#             */
/*   Updated: 2025/03/04 14:11:18 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DEBUG_H
# define DEBUG_H

int	debug_get_fd(void);

# define DEBUG(...)	dprintf(debug_get_fd(), __VA_ARGS__)
# define DEBUG_CLOSE() close(debug_get_fd())

#endif
