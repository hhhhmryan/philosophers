# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mryan <mryan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/27 18:31:17 by mryan             #+#    #+#              #
#    Updated: 2021/07/28 14:33:25 by mryan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

HEADER = philosophers.h

SRCS = philosophers.c \
	parse.c \
	init.c \
	lib_functions.c \
	lib_functions_2.c \
	utils.c \
	message.c \
	cycle.c \
	monitor.c \


CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(OBJ) -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re