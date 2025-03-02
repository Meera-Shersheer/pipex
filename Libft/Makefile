SRC= ft_chars_a.c ft_chars_b.c ft_mem_a.c ft_mem_b.c ft_puts.c ft_string_a.c ft_string_b.c ft_string_c.c ft_split.c ft_printf.c put_printf.c support_printf.c \
get_next_line_bonus.c get_next_line_utils_bonus.c
BNS= ft_linked_lists_a_bonus.c ft_linked_lists_b_bonus.c
NAME = libft.a

CC= cc

CFLAGS= -Wall -Wextra -Werror -g

OBJECTDIR := objects

OBJ_SRC = $(addprefix $(OBJECTDIR)/, $(SRC:.c=.o))
OBJ_BNS = $(addprefix $(OBJECTDIR)/, $(BNS:.c=.o))

all: $(NAME)

$(NAME): | $(OBJ_SRC)
	ar rcs $(NAME) $(OBJ_SRC)


$(OBJECTDIR)/%.o: %.c
	@mkdir -p $(OBJECTDIR) 
	$(CC) $(CFLAGS) -c $< -o $@

bonus:  $(NAME) $(OBJ_BNS)
	ar rcs $(NAME) $(OBJ_SRC) $(OBJ_BNS)

clean:
	rm -rf $(OBJECTDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus       	
  	
