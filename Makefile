NAME			=	minishell
DIR_SRC			=	./src
DIR_BUILD		=	./build
SOURCES			=	builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c builtin/export.c builtin/get_builtin.c builtin/pwd.c builtin/unset.c executor/commands.c executor/executor.c input/get_next_line.c input/handle_state.c input/handle_state_var.c input/handle_transition.c input/input_parse.c input/input_read.c main.c shell.c utils/string.c 
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
