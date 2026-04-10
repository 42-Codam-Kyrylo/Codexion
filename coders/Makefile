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
INC_DIR = include
SRC_DIR = src

OBJ_DIR = obj

SRC = \
	$(SRC_DIR)/core/main.c \
	$(SRC_DIR)/core/helpers.c \
	$(SRC_DIR)/core/parsing.c \
	$(SRC_DIR)/heap/heap.c \
	$(SRC_DIR)/heap/heap_helpers.c \
	$(SRC_DIR)/init/initialization_coders.c \
	$(SRC_DIR)/init/initialization_common.c \
	$(SRC_DIR)/coder/coder_routine.c
	
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)


$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(DEPFLAGS) -c $< -o $@

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
