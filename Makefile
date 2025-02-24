NAME			=	minishell
DIR_SRC			=	./src
DIR_BUILD		=	./build
SOURCES			=	ast/ast_create.c ast/ast_parse.c ast/ast_parse_pipe.c ast/ast_parse_subshell.c ast/ast_utils.c builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c builtin/export.c builtin/pwd.c builtin/unset.c debug_general.c exec/exec_ast.c exec/exec_bin.c exec/exec_child.c exec/exec_command.c exec/exec_logical.c exec/exec_pipeline.c exec/exec_redirect.c exec/exec_utils.c input/get_next_line.c input/input_read.c lexer/lex.c lexer/lex_eof_checker.c lexer/lex_eof_quotes.c lexer/lex_eof_var.c lexer/lexer_action.c lexer/lexer_action_var.c lexer/lexer_state.c main.c shell.c utils/debug.c utils/error.c utils/libft_extra.c utils/string.c utils/string_array.c utils/string_array_find.c utils/string_array_find_last.c utils/string_array_match.c utils/string_array_slice.c 
SOURCES_NAME	=	$(basename $(SOURCES))
OBJECTS			=	$(addsuffix .o, $(addprefix $(DIR_BUILD)/, $(SOURCES_NAME)))
FLAGS			=	-Wall -Wextra -Werror -g

LIBFT			=	./lib/libft
LIBS_INCLUDE	=	-I$(LIBFT) -I$(DIR_SRC)
LIBS_LINK_DIR	=	-L$(LIBFT)
LIBS_LINK		=	-lft -lreadline

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -sC $(LIBFT)
	@cc $(OBJECTS) $(FLAGS) $(LIBS_LINK_DIR) $(LIBS_LINK) -o $@

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(dir $@)
	@cc $(FLAGS) $(LIBS_INCLUDE) -c $^ -o $@

clean:
	make clean -C $(LIBFT)
	rm -rf $(DIR_BUILD)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean all