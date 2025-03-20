# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 18:55:54 by wweerasi          #+#    #+#              #
#    Updated: 2025/03/19 16:06:49 by wweerasi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

GNL_DIR = gnl
PRINTF_DIR = printf_fd

SOURCES = ft_isalpha.c \
		  ft_isdigit.c \
		  ft_isalnum.c \
		  ft_isascii.c \
		  ft_isprint.c \
		  ft_strlen.c \
		  ft_memset.c \
		  ft_bzero.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_strlcpy.c \
		  ft_strlcat.c \
		  ft_toupper.c \
		  ft_tolower.c \
		  ft_strchr.c \
		  ft_strcmp.c \
		  ft_strrchr.c \
		  ft_strncmp.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_strnstr.c \
		  ft_atoi.c \
		  ft_atof.c \
		  ft_calloc.c \
		  ft_strdup.c \
		  ft_substr.c \
		  ft_strjoin.c \
		  ft_strtrim.c \
		  ft_split.c \
		  ft_itoa.c \
		  ft_strmapi.c \
		  ft_striteri.c \
		  ft_putchar_fd.c \
		  ft_putstr_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \

BONUS_SOURCES = ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c \

GNL_SOURCES = $(GNL_DIR)/get_next_line.c

PRINTF_SOURCES = $(PRINTF_DIR)/printf_fd.c \
				 $(PRINTF_DIR)/putnbr_fd.c \
		  		 $(PRINTF_DIR)/putnbr_u_fd.c \
				 $(PRINTF_DIR)/putstr_fd.c \
				 $(PRINTF_DIR)/putchar_fd.c \

OBJECTS = $(SOURCES:.c=.o)
BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)
GNL_OBJECTS = $(notdir $(GNL_SOURCES:.c=.o))
PRINTF_OBJECTS = $(notdir $(PRINTF_SOURCES:.c=.o))

HEADER = libft.h $(GNL_DIR)/get_next_line.h $(PRINTF_DIR)/printf_fd.h

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

AR = ar rcs

all: $(NAME)

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: $(GNL_DIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: $(PRINTF_DIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(GNL_OBJECTS) $(PRINTF_OBJECTS)
	$(AR) $(NAME) $(OBJECTS) $(GNL_OBJECTS) $(PRINTF_OBJECTS)

bonus: .bonus

.bonus:$(NAME) $(BONUS_OBJECTS)
	$(AR) $(NAME) $(BONUS_OBJECTS)
	@touch .bonus

clean:
	$(RM) $(OBJECTS) $(BONUS_OBJECTS) $(GNL_OBJECTS) $(PRINTF_OBJECTS)
	@$(RM) .bonus

fclean: clean
	$(RM) $(NAME)
	@$(RM) .bonus

re: fclean all

.PHONY: all clean fclean re bonus 
