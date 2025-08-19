NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

INCLUDE = -Iinclude -I$(LIBFT_DIR)

SRCS		= \
				src/
				
OBJS = $(SRCS:src/%.c=obj/%.o)
GREEN		= \033[0;32m
GREY		= \033[0;90m
RED			= \033[0;31m
RESET		= \033[0m

all: $(NAME)

$(LIBFT):
	@echo "$(GREY)Compiling libft...$(RESET)"
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS) include/minishell.h 
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)Executable created: $(NAME)$(RESET)"

obj/%.o: src/%.c include/minishell.h $(LIBFT_DIR)/libft.h
	@mkdir -p obj
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) -r obj
	$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(RED)Cleaned object files.$(RESET)"

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(RED)Fully cleaned everything.$(RESET)"
re: fclean all

.PHONY: all clean fclean re run valgrind
