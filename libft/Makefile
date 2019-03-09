# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/25 18:27:37 by mpetruno          #+#    #+#              #
#    Updated: 2019/03/05 19:25:25 by mpetruno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

FLAGS = -Wall -Werror -Wextra

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./includes/
FT_PRINTF_DIR = ft_printf/

H_FILES = libft.h ft_printf.h

HEADERS = $(addprefix $(INC_DIR), $(H_FILES))

FUNC_LIST = memset \
			bzero \
			memcpy \
			memccpy \
			memmove \
			memchr \
			memcmp \
			strlen \
			numlen \
			strdup \
			strcpy \
			substr \
			strncpy \
			strcat \
			strncat \
			strlcat \
			strchr \
			strchrr \
			strrchr \
			strstr \
			strnstr \
			strcmp \
			strequ \
			strncmp \
			atoi \
			isupper \
			islower \
			isalpha \
			isdigit \
			isnumeric \
			isalnum \
			isascii \
			isprint \
			toupper \
			tolower \
			memalloc \
			realloc \
			memdel \
			strnew \
			strdel \
			strclr \
			striter \
			striteri \
			strmap \
			strmapi \
			strequ \
			strnequ \
			strsub \
			strjoin \
			strjoin3 \
			strtrim \
			strsplit \
			itoa \
			putchar \
			putstr \
			putendl \
			putnbr \
			putchar_fd \
			putstr_fd \
			putendl_fd \
			putnbr_fd \
			lstnew \
			lstdelone \
			lstdel \
			lstfree \
			lstadd \
			lstins \
			lstinsuniq \
			lstiter \
			lstsize \
			lstmap \
			lltoa_base \
			ulltoa_base \
			dtoa \
			strsort \
			strarr_sort \
			arrsize

PRINTF_FILES = ft_printf.c \
				parsing.c \
				print_arg.c \
				arg_to_str_n.c \
				arg_to_str_s.c \
				print_nums.c \
				print_str.c \
				output.c

OTHER_FILES = get_next_line.c

SRC_LIST = $(addsuffix .c, $(addprefix ft_, $(FUNC_LIST))) \
			$(addprefix $(FT_PRINTF_DIR), $(PRINTF_FILES)) \
			$(OTHER_FILES)

OBJ_LIST = $(addprefix $(OBJ_DIR), $(SRC_LIST:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_LIST)
	@ar -rc $(NAME) $(OBJ_LIST)
	@ranlib $(NAME)
	@echo "$(NAME) - Done."

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(FT_PRINTF_DIR)
	$(CC) $(FLAGS) -I $(INC_DIR) -c $^ -o $@

clean:
	@echo "$(NAME): Cleaning object files... "
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(NAME): Removing $(NAME)... "
	@rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re
