NAME			=	minishell
DIR_SRC			=	./src
DIR_BUILD		=	./build
SOURCES			=	main.c 
SOURCES_NAME	=	$(basename $(SOURCES))
OBJECTS			=	$(addsuffix .o, $(addprefix $(DIR_BUILD)/, $(SOURCES_NAME)))
FLAGS			=	-Wall -Wextra -Werror

LIBFT			=	./lib/libft
LIBS_INCLUDE	=	-I$(LIBFT)
LIBS_LINK_DIR	=	-L$(LIBFT)
LIBS_LINK		=	-lft

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -sC $(LIBFT)
	@cc $(OBJECTS) $(FLAGS) $(LIBS_LINK_DIR) $(LIBS_LINK) -o $@

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c | $(DIR_BUILD)
	@cc $(FLAGS) $(LIBS_INCLUDE) -c $^ -o $@

$(DIR_BUILD):
	@mkdir -p $@

clean:
	make clean -C $(LIBFT)
	rm -rf $(DIR_BUILD)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean all
