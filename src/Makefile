NAME        = minishell

DIR_LIBFT   = ./lib/libft
DIR_SRC     = ./src
DIR_OBJ     = $(DIR_SRC)/objects
DIR_INC     = ./includes

HEADERS     = $(DIR_INC)/minishell.h

SOURCES = \
    main/main.c \
    main/msh_clean.c \
    main/msh_error.c \
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
    parse_new/parse.c \
    parse_new/tokenize.c \
    validate/checker.c \
    validate/pipe_trailing.c \
    validate/redirections.c \
    validate/validate.c

OBJECTS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))
DEPS    = $(OBJECTS:.o=.d)

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I$(DIR_INC) -MMD -MP
RM      = rm -rf

LIBFT_FLAGS = -L $(DIR_LIBFT) -lft

all: libft $(NAME)

libft:
    @make -C $(DIR_LIBFT)

$(NAME): $(OBJECTS)
    $(CC) $(OBJECTS) $(LIBFT_FLAGS) -o $@

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