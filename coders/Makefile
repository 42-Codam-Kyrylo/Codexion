# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kvolynsk <kvolynsk@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2026/03/24 20:16:47 by kvolynsk      #+#    #+#                  #
#    Updated: 2026/04/10 20:49:02 by kvolynsk      ########   odam.nl          #
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
	$(SRC_DIR)/core/launch_routines.c \
	$(SRC_DIR)/heap/heap.c \
	$(SRC_DIR)/heap/heap_helpers.c \
	$(SRC_DIR)/init/initialization_coders.c \
	$(SRC_DIR)/init/initialization_common.c \
	$(SRC_DIR)/init/initialization_dongles.c \
	$(SRC_DIR)/init/initialization_monitor.c \
	$(SRC_DIR)/coder/coder_helpers.c \
	$(SRC_DIR)/coder/coder_routine.c \
	$(SRC_DIR)/coder/coder_actions.c \
	$(SRC_DIR)/coder/coder_utils.c \
	$(SRC_DIR)/monitor/monitor_routine.c \
	
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
	./$(NAME) 5 500 100 100 100 5 50 fifo

.PHONY: all clean fclean re run

-include $(DEP)
