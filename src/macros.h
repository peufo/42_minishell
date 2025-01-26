#ifndef MACROS_H
# define MACROS_H

//////////////////////////////////////////
// -----===== ERROR MESSAGES =====----- //
//////////////////////////////////////////

# define BAD_SYNTAX 1000
# define BAD_PARENTHESIS 1001
# define NO_INPUT_FILE 1002
# define MALLOC_ERROR 1003
# define OUVERTURE 1004
# define LALALA 1005	

//////////////////////////////////////
// -----===== LEXER PART =====----- //
//////////////////////////////////////

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
# define L_WHITESPACE 10
# define L_PARENTHESIS 11
# define L_GATE 12
# define L_WORD 13
# define UNKNOWN_TOKEN 14

# define L_PROCESS_GATE 20
# define PIPE 21
# define AND_GATE 22
# define OR_GATE 23

# define L_PROCESS_DIR 30
# define RIGHT_RDIR 31
# define LEFT_RDIR 32
# define RIGHT_DRDIR 33
# define LEFT_DRDIR 34
# define L_LDIR 35
# define L_RDIR 36

# define L_PROCESS_FLAG 40
# define L_SINGLE_FLAG 41
# define L_DOUBLE_FLAG 42

# define S0 50
# define D1 51
# define D2 52
# define D3 53
# define D4 54
# define D5 55
# define Q1 56
# define Q2 57
# define Q3 58
# define Q4 59
# define Q5 60
# define S1 61

////////////////////////////////////////
// -----===== PARSING PART =====----- //
////////////////////////////////////////

# define OK 999
# define KO 666

//////////////////////////////////////
// -----====== FUNCTIONS =====----- //
//////////////////////////////////////

# define MAIN 2001
# define SHELL_INIT 2002
# define SHELL_EXEC 2003
# define SHELL_EXIT 2004

# define INPUT_READ 2005

/////////////////////////////////
// -----===== UTILS =====----- //
/////////////////////////////////

# define STRING_ENSURE_MALLOC 2010
# define STRING_PUSH 2011
# define STRING_FREE 2012

/////////////////////////////////
// -----===== LEXER =====----- //
/////////////////////////////////

# define CHECK_ERRORS 2020
# define CHECK_ERRORS2 2021
# define CHECK_ERRORS3 2022
# define CHECK_ERRORS4 2023
# define CHECK_ERRORS5 2024

# define LEX 2030
# define TOKENISE 2031
# define TOKENISE_GATES 2032
# define TOKENISE_QUOTES 2033
# define TOKENISE_DIRECTION 2034
# define TOKENISE_COMMENT 2035
# define TOKENISE_PIPES 2036
# define TOKENISE_VARIABLE 2037
# define TOKEN_PARENTHESIS 2038
# define GET_CHAR_STATE 2039

//////////////////////////////////
// -----===== PARSER =====----- //
//////////////////////////////////

# define PARSE 2100
# define PRINT_PARSE 2101

////////////////////////////////////
// -----===== EXECUTOR =====----- //
////////////////////////////////////

///////////////////////////////////
// -----===== BUILTIN =====----- //
///////////////////////////////////

/////////////////////////////////
// -----===== UTILS =====----- //
/////////////////////////////////

#endif