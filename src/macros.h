#ifndef MACROS_H
# define MACROS_H

// -----===== ERROR MESSAGES =====----- //

# define BAD_SYNTAX 1000
# define BAD_PARENTHESIS 1001
# define NO_INPUT_FILE 1002
# define LALALA 1003

// -----===== LEXER PART =====----- //

# define BULLSHIT -1
# define L_NO_STATE 0
# define L_INIT 1
# define L_DEFAULT 2
# define L_QUOTE 3
# define L_DQUOTE 4
# define L_VAR 5
# define L_DVAR 6
# define L_IGNORE 7
# define L_PAR_OPEN 8
# define L_PAR_CLOSE 9

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

# define OK 999
# define KO 666

#endif