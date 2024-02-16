# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 17:13:25 by pedmonte          #+#    #+#              #
#    Updated: 2024/01/31 18:23:13 by pedmonte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -pthread
CFLAGS = -Wall -Wextra -Werror

NAME = philosophers

OBJ_PATH = objs
HEADER = includes
SRC_PATH = src

SOURCES = main.c

SRCS := $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS := $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	@echo "Project successfully compiled"


$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c -o $@ $< -I$(HEADER)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

clean:
	@echo "Cleaning object files"
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
