# ───────────────────────────────────────────────────────────────
#                     CONFIGURATION
# ───────────────────────────────────────────────────────────────
NAME        = test_msh
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -fsanitize=address,undefined

LIBFT_DIR   = ../lib/libft
LIBFT_A     = $(LIBFT_DIR)/libft.a
LIBFT       = -L$(LIBFT_DIR) -lft
READLINE    = -lreadline

INCLUDES    = -Iincludes -I$(LIBFT_DIR)

# ───────────────────────────────────────────────────────────────
#                     SOURCE FILES
# ───────────────────────────────────────────────────────────────

# Source files from subdirectories
VALID_SRC  = $(wildcard ../validate/*.c)
PARSE_SRC   = $(wildcard ./prse/*.c)
EXPAND_SRC  = $(wildcard ../signal/*.c)
PARSE_UTILS_SRC  = $(wildcard ../signal/*.c)
SIGNAL_SRC  = $(wildcard ../signal/*.c)

# Main file is in the root directory
TEST_MAIN   = ./test_main.c

# All sources needed to build test_msh
SRC = $(filter-out ./test_main.c, $(PARSE_SRC)) $(SIGNAL_SRC) $(TEST_MAIN)
OBJ         = $(SRC:.c=.o)

# ───────────────────────────────────────────────────────────────
#                     BUILD TARGETS
# ───────────────────────────────────────────────────────────────

all: $(NAME)

$(NAME): libft $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(LIBFT) $(READLINE) -o $(NAME)

# ───────────────────────────────────────────────────────────────
#              Build libft if not already built
# ───────────────────────────────────────────────────────────────

libft:
	@echo "🔧 Building libft..."
	@make -C $(LIBFT_DIR)

# ───────────────────────────────────────────────────────────────
#                        CLEANUP
# ───────────────────────────────────────────────────────────────

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libft
