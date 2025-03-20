NAME			=	minishell
DIR_SRC			=	./src
DIR_BUILD		=	./build
SOURCES			=	ast/ast_create.c ast/ast_debug.c ast/ast_parse.c ast/ast_parse_command.c ast/ast_parse_heredoc.c ast/ast_parse_pipe.c ast/ast_parse_subshell.c ast/ast_parse_tilde.c ast/ast_parse_wildcard.c ast/ast_utils.c builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c builtin/export.c builtin/export_print.c builtin/pwd.c builtin/unset.c debug_general.c exec/exec_ast.c exec/exec_bin.c exec/exec_child.c exec/exec_command.c exec/exec_heredoc.c exec/exec_logical.c exec/exec_pipeline.c exec/exec_utils.c input/check_errors.c input/checkers_input.c input/get_next_line.c input/input_read.c input/prompt.c lex_eof/lex_eof.c lex_eof/lex_eof_checkers.c lex_eof/lex_eof_geters.c lex_eof/lex_eof_help_redir.c lex_eof/lex_eof_redir.c lex_eof/lex_eof_stack_commands.c lexer/lex.c lexer/lexer_action.c lexer/lexer_action_var.c lexer/lexer_action_var_dquote.c lexer/lexer_state.c main.c shell/shell.c shell/shell_exec.c utils/get_line.c utils/libft_extra.c utils/libft_extra2.c utils/string.c utils/string_array.c utils/string_array_dup.c utils/string_array_find.c utils/string_array_find_last.c utils/string_array_join.c utils/string_array_match.c utils/string_array_slice.c utils/string_array_sort.c utils/throw_error.c utils/waitstatus.c 
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
