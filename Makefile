
NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBS    = -lreadline -lncurses
INCLUDES = -I. -I$(LIBFT_DIR) 
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CFILES = minishell.c tokenizing.c
OFILES = $(CFILES:.c=.o)

.PHONY: all clean fclean re 

all: $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OFILES) $(LIBFT_LIB) 
	$(CC) $(CFLAGS) $(INCLUDES) $(OFILES) $(LIBFT_LIB) -o $(NAME) $(LIBS)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OFILES)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all