NAME            =   minishell
DIR_SRC         =   ./src
DIR_BUILD       =   ./build

BUILTIN_SRC     =   src/builtin/cd.c src/builtin/echo.c src/builtin/env.c \
                   src/builtin/exit.c src/builtin/export.c src/builtin/get_builtin.c \
                   src/builtin/pwd.c src/builtin/unset.c

EXECUTOR_SRC    =   src/executor/executor.c

INPUT_SRC       =   src/input/get_next_line.c src/input/input_read.c

LEXER_SRC       =   src/lexer/lex.c src/lexer/lex_helpers.c src/lexer/handle_quotes_and_var.c \
					src/lexer/check_errors.c \

PARSER_SRC      =   src/parser/parse.c src/parser/arguments.c src/parser/priority.c \
					src/parser/special_commands.c

UTILS_SRC       =   src/utils/string.c src/utils/string_array.c src/utils/string_array_find.c \
                   src/utils/error_messages.c src/utils/lib_plus_ft.c src/utils/track_function.c

SOURCES         =   $(BUILTIN_SRC) $(EXECUTOR_SRC) $(INPUT_SRC) $(LEXER_SRC) src/main.c src/shell.c $(PARSER_SRC) $(UTILS_SRC)

OBJECTS         =   $(SOURCES:src/%.c=$(DIR_BUILD)/%.o)

FLAGS           =   -Wall -Wextra -Werror -g

LIBFT           =   ./lib/libft
LIBS_INCLUDE    =   -I$(LIBFT) -I$(DIR_SRC)
LIBS_LINK_DIR   =   -L$(LIBFT)
LIBS_LINK       =   -lft -lreadline

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -sC $(LIBFT)  # Compilation de libft
	@cc $(OBJECTS) $(FLAGS) $(LIBS_LINK_DIR) $(LIBS_LINK) -o $@  # Compilation finale

$(DIR_BUILD)/%.o: src/%.c | $(DIR_BUILD)
	@mkdir -p $(dir $@)  # Création du répertoire cible
	@cc $(FLAGS) $(LIBS_INCLUDE) -c $< -o $@  # Compilation du fichier source

$(DIR_BUILD):
	@mkdir -p $(DIR_BUILD)

clean:
	make clean -C $(LIBFT)  # Nettoyage de libft
	rm -rf $(DIR_BUILD)  # Suppression du répertoire build

fclean: clean
	make fclean -C $(LIBFT)  # Nettoyage de libft
	rm -f $(NAME)  # Suppression du binaire

re: fclean all
