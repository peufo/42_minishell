/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:20:16 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/30 15:18:14 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

////////////////////////////////////////
// -----======== ERRORS ========----- //
////////////////////////////////////////

#define WHERE __FILE__, __LINE__

////////////////////////////////////////
// -----======== TOKENS ========----- //
////////////////////////////////////////

# define TOKEN_GROUP_REDIRECT "<><<>>"
# define TOKEN_GROUP_LOGICAL "&&||"
# define TOKEN_GROUP_COMMAND "echo"
# define TOKEN_GROUP_SUBSHELL "[]"
# define TOKEN_GROUP_COMPOUND_LIST "()"

# define TOKEN_PIPELINE "|"
# define TOKEN_SUFFIX "<"
# define TOKEN_DGREAT ">>"
# define TOKEN_DLESS "<<"
# define TOKEN_GREAT ">"
# define TOKEN_LESS "<"
# define TOKEN_WORD "word"
# define TOKEN_VAR "$"
# define TOKEN_VAR_STATUS "$?"
# define TOKEN_OR "||"
# define TOKEN_AND "&&"
# define TOKEN_FILE "fd"
# define TOKEN_UNKNOWN "???"
# define TOKEN_PAR_OPEN "("
# define TOKEN_PAR_CLOSE ")"

#endif