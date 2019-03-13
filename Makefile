# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/06 15:38:01 by mpetruno          #+#    #+#              #
#    Updated: 2019/03/12 13:52:00 by mpetruno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

CC = gcc

FLAGS = -Wall -Werror -Wextra -g -fsanitize=leak# -fsanitize=address

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./includes/
LIB_DIR = ./libft/
LIB_INC_DIR = $(LIB_DIR)includes/
LIB = $(LIB_DIR)libft.a

DIR_LST =	$(OBJ_DIR) \
			$(OBJ_DIR)hashmap/

MAIN_FILES =	main.c \
				hashmap/hashmap.c \
				hashmap/hm_util.c \
				node.c \
				farm.c \
				lex_func1.c \
				lex_func2.c \
				token_check.c \
				path.c
				



SRC_LIST = $(MAIN_FILES) \
			$(addprefix $(BUILTIN_DIR), $(BUILTIN))

OBJ_LIST = $(addprefix $(OBJ_DIR), $(SRC_LIST:.c=.o))

all: $(NAME)

$(NAME): $(LIB) $(DIR_LST) $(OBJ_LIST)
	@$(CC) $(OBJ_LIST) $(LIB) -o $(NAME) $(FLAGS)
	@echo "$(NAME) - Done."

$(LIB):
	@make -C $(LIB_DIR) all --silent

$(DIR_LST):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -I $(INC_DIR) -I $(LIB_INC_DIR) -c $^ -o $@


clean:
	@echo "$(NAME): Cleaning object files... "
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR) clean --silent

fclean: clean
	@echo "$(NAME): Removing $(NAME)... "
	@rm -f $(NAME)
	@make -C $(LIB_DIR) fclean --silent

re: fclean all

.PHONY = all clean fclean re
