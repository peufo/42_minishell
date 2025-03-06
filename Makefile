NAME			=	minishell
DIR_SRC			=	./src
DIR_BUILD		=	./build
SOURCES			=	ast/ast_create.c ast/ast_debug.c ast/ast_parse.c ast/ast_parse_pipe.c ast/ast_parse_subshell.c ast/ast_utils.c builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c builtin/export.c builtin/pwd.c builtin/unset.c debug_general.c exec/exec_ast.c exec/exec_bin.c exec/exec_child.c exec/exec_command.c exec/exec_logical.c exec/exec_pick_redirections.c exec/exec_pipeline.c exec/exec_utils.c input/checkers_input.c input/get_next_line.c input/input_read.c lex_eof/checkers.c lex_eof/input_handle_redir.c lex_eof/lex_eof.c lex_eof/lex_eof_stack_commands.c lex_eof/lex_eof_utils.c lexer/lex.c lexer/lexer_action.c lexer/lexer_action_var.c lexer/lexer_state.c main.c shell/shell.c shell/shell_exec.c utils/error.c utils/libft_extra.c utils/string_array.c utils/string_array_find.c utils/string_array_find_last.c utils/string_array_match.c utils/string_array_slice.c utils/string.c utils/waitstatus.c 
SOURCES_NAME	=	$(basename $(SOURCES))
OBJECTS			=	$(addsuffix .o, $(addprefix $(DIR_BUILD)/, $(SOURCES_NAME)))
CFLAGS			=	-Wall -Wextra -Werror -g

LIBFT			=	./lib/libft
LDINCLUDE		=	-I$(LIBFT) -I$(DIR_SRC)
LDFLAGS			=	-L$(LIBFT)
LDLIBS			=	-lft -lreadline

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(MAKE) -sC $(LIBFT)
	@$(CC) $(OBJECTS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(LDINCLUDE) -c $^ -o $@

clean:
	$(MAKE) clean -C $(LIBFT)
	$(RM) -r $(DIR_BUILD)

fclean: clean
	$(MAKE) fclean -C $(LIBFT)
	$(RM) $(NAME)

re: fclean all
