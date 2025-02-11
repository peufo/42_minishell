NAME			=	minishell
DIR_SRC			=	./src
DIR_BUILD		=	./build
SOURCES			=	builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c builtin/export.c builtin/get_builtin.c builtin/pwd.c builtin/unset.c debug2.c debug.c executor/executor.c input/get_next_line.c input/input_read.c lexer/lex.c lexer/lexer_action.c lexer/lexer_action_var.c lexer/lexer_state.c main.c parser/parse.c parser/parse_checkers.c parser/parse_geters.c parser/parse_inits.c parser/parse_script.c parser/parse_simple_utils.c parser/parse_subshell.c parser/parse_utils.c shell.c utils/debug.c utils/error.c utils/lib_extra2.c utils/libft_extra.c utils/string_array.c utils/string_array_find.c utils/string.c 
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