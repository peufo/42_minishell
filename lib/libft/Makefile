NAME = libft.a
NAME_SO = libft.so
DIR_SRC = ./
DIR_BUILD = build
FLAGS = -Wall -Wextra -Werror

SOURCES		=	ft_delete_chars.c ft_include.c ft_isempty.c ft_strcat_arr ft_startwith ft_endwith ft_isspace ft_stradd.c ft_strcat.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strcut.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strcmp.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
FUNCTIONS	=	$(subst .c,,$(notdir $(SOURCES)))
OBJECTS		=	$(addsuffix .o, $(addprefix $(DIR_BUILD)/, $(FUNCTIONS)))

SOURCES_BNS		=	ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c
FUNCTIONS_BNS	=	$(subst .c,,$(notdir $(SOURCES_BNS)))
OBJECTS_BNS		=	$(addsuffix .o, $(addprefix $(DIR_BUILD)/, $(FUNCTIONS_BNS)))

OS			=	$(shell uname -s)
LIBS = -L. -lft
ifeq ($(OS),Linux)
	LIBS += -lbsd -ldl
endif

all: $(NAME) bonus

$(NAME): $(OBJECTS)
	@ar -cr $@ $^

bonus: $(OBJECTS_BNS)
	@ar -cr $(NAME) $(OBJECTS_BNS)

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c | $(DIR_BUILD)
	@cc $(FLAGS) -c $^ -o $@

$(DIR_BUILD):
	@mkdir $(DIR_BUILD)

so: $(OBJECTS)
	@cc -nostartfiles -shared -o libft.so $(OBJECTS)

clean:
	rm -rf $(DIR_BUILD)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_SO)

re: fclean all
