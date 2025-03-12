SRC= pipex_utils.c pipex.c check_cmd.c execute_cmd.c 
BNS= pipex_utils_bonus.c pipex_bonus.c check_cmd_bonus.c execute_cmd_bonus.c ft_dlist_help_1_bonus.c\
ft_dlist_help_2_bonus.c ft_dlist_help_3_bonus.c

NAME = pipex
BNS_NAME = pipex

CC= cc
CFLAGS= -Wall -Wextra -Werror -g3 
#-fsanitize=address -g

LFTDIR := ./Libft

SRC_DIR := src
OBJ_DIR := obj

SRC_PATH = $(addprefix $(SRC_DIR)/, $(SRC))
BNS_PATH = $(addprefix $(SRC_DIR)/, $(BNS))


OBJ_SRC = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_PATH))
OBJ_BNS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(BNS_PATH))

all: $(NAME)

$(NAME): $(OBJ_SRC) | libft
	$(CC) $(CFLAGS) $(OBJ_SRC) -o $(NAME) -L$(LFTDIR) -lft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
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