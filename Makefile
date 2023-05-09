# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 16:30:17 by tmiftah           #+#    #+#              #
#    Updated: 2023/05/10 00:04:39 by tmiftah          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC = philo.c \
		start.c

OBJ = ${SRC:%.c=%.o}

NAME = philo

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

re : fclean all

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
