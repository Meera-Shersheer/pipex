SRC=
BNS=

NAME = pipex
CC= cc
CFLAGS= -Wall -Wextra -Werror
#-g3 -fsanitize=address -g

BNS_NAME = pipex
#PATH LIB
LFTDIR= ./Libft

## create an object dir 
OBJ_DIR := obj

OBJ_SRC = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_BNS = $(addprefix $(OBJ_DIR)/, $(BNS:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_SRC) | libft
	$(CC) $(CFLAGS) $(OBJ_SRC) -o $(NAME) -L$(LFTDIR) -lft

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR) 
	$(CC) $(CFLAGS) -c $< -o $@

libft: 
	@$(MAKE) -sC $(LFTDIR) bonus

clean:
	@rm -rf $(OBJ_SRC) $(OBJ_DIR)
	@$(MAKE) -sC $(LFTDIR) clean

bonus: $(OBJ_BNS)| libft 
	$(CC) $(CFLAGS) $(OBJ_BNS) -o $(BNS_NAME) -L$(LFTDIR) -lft

fclean: clean
	@rm -f $(OBJ_SRC) 
	@$(MAKE) -C $(LFTDIR) fclean 
	@rm $(NAME)

re: fclean all

.PHONY: all clean fclean re libft bonus  