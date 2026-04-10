# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kvolynsk <kvolynsk@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2026/03/24 20:16:47 by kvolynsk      #+#    #+#                  #
#    Updated: 2026/03/31 22:13:38 by kvolynsk      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = coders

CC = cc
CFLAGS = -Wall -Wextra -Werror
DEPFLAGS = -MMD -MP

OBJ_DIR = obj

SRC = \
	main.c \
	helpers.c \
	parsing.c \
	heap.c \
	heap_helpers.c \
	initialization.c \
	initialization_helpers.c \
	coder_routine.c \
	
	
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)


$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(DEP)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME) 5 1000 100 100 100 25 50 fifo

.PHONY: all clean fclean re run

-include $(DEP)
