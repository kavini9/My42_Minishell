 NAME        = minishell

DIR_LIBFT   = ./lib/libft
DIR_SRC     = ./src
DIR_OBJ     = $(DIR_SRC)/objects
DIR_INC     = ./includes

HEADERS     = $(DIR_INC)/minishell.h

#vpath %.c main/ builtin/ envl/

SOURCES = main/main.c \
	  main/msh_clean.c \
	  main/msh_error.c \
	  validate/checker.c \
	  validate/redirections.c \
	  validate/validate.c \
	  parse/parse.c \
	  parse/tokenize.c \
	  parse/parse_utils.c \
	  parse/expand.c \
	  parse/expand_array_utils.c \
	  parse/exp_struct_manager.c \
	  parse/setup_cmd.c \
	  builtin/cd.c \
	  builtin/cd_unlinked_dir.c \
	  builtin/echo.c \
	  builtin/env.c \
	  builtin/exec_builtin.c \
	  builtin/exit.c \
	  builtin/export.c \
	  builtin/pwd.c \
	  builtin/unset.c \
	  envl/init_envp.c \
	  envl/utils_envl.c \
	  execute/exec_cmd.c \
	  execute/execin_child.c \
	  execute/heredoc.c \
	  execute/redir.c \
	  signal/signal_handler.c \
	  signal/signal_utils.c

OBJECTS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))
DEPS    = $(OBJECTS:.o=.d) #what is  this?

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I$(DIR_INC) -MMD -MP 
RM      = rm -rf

LIBFT_FLAGS = -L $(DIR_LIBFT) -lft

all: libft $(NAME)

libft:
	@make -C $(DIR_LIBFT)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBFT_FLAGS) -lreadline -o $@ 
#see where exactly to add readline flags
#-g -fsanitize=address

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	@$(RM) $(DIR_OBJ)
	@make -C $(DIR_LIBFT) clean

fclean: clean
	@$(RM) $(NAME)
	@make -C $(DIR_LIBFT) fclean

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all libft clean fclean re debug
