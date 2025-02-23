# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 15:26:29 by wweerasi          #+#    #+#              #
#    Updated: 2025/01/21 20:03:43 by wweerasi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

DIR_LIBFT 	= ./lib/libft
DIR_SRC		= ./src
DIR_OBJ		= $(DIR_SRC)/objects
DIR_INC		= ./includes
HEADERS		= $(DIR_INC)/pipex.h

SOURCES = pipex_main.c \
	  pipex.c \
	  pipex_init.c \
	  pipex_cmd.c \
	  pipex_exit.c \


OBJECTS		= $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))

LIBFT_FLAGS	= -L $(DIR_LIBFT) -lft

CC		= cc
CFLAGS		= -Wall -Wextra -Werror
RM		= rm -rf

all: libft $(NAME)

libft:
	@make -C $(DIR_LIBFT)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBFT_FLAGS) -o $@

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HEADERS) | $(DIR_OBJ)
	@$(CC) $(CFLAGS) -I$(DIR_INC) -c $< -o $@

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

clean:
	@$(RM) $(DIR_OBJ)
	@make -C $(DIR_LIBFT) clean

fclean: clean
	@$(RM) $(NAME)
	@make -C $(DIR_LIBFT) fclean

re: fclean all

.PHONY: all libft clean fclean re
