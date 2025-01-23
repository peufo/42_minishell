#ifndef MACROS_H
# define MACROS_H

// -----===== LEXER PART =====----- //

# define BULLSHIT -1
# define L_NO_STATE 0
# define L_INIT 1
# define L_DEFAULT 2
# define L_QUOTE 3
# define L_DQUOTE 33
# define L_VAR 4
# define L_DVAR 44
# define L_IGNORE 5
# define L_PAR_OPEN 6
# define L_PAR_CLOSE 7

# define L_PROCESS_GATE 20
# define PIPE 21
# define AND_GATE 22
# define OR_GATE 23

# define L_PROCESS_DIR 30
# define RIGHT_RDIR 31
# define LEFT_RDIR 32
# define RIGHT_DRDIR 33
# define LEFT_DRDIR 34

# define L_PROCESS_FLAG 40
# define L_SINGLE_FLAG 41
# define L_DOUBLE_FLAG 42

// -----===== PARSING PART =====----- //

#endif