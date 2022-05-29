# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/25 01:41:18 by mchliyah          #+#    #+#              #
#    Updated: 2022/05/28 22:05:37 by mchliyah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread

RM = rm -f

FILES = \
		main.c\
		utils.c\
		start.c	\
		error.c\
		print.c\

OBJECTS = $(FILES:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

C_RED = \033[1;31m
C_GREEN = \033[1;32m
C_L_BLUE = \033[1;34m
C_RES = \033[0m

.PHONY : all clean fclean

all : $(NAME)

$(NAME) :  $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(C_GREEN)[philosophers MANDATORY CREATED!]$(C_RES)"

clean : 
	@$(RM) $(OBJECTS)
	@echo "$(C_RED)[philosophers OBJECTS DELETED!]$(C_RES)"

fclean : clean
	@$(RM) $(NAME)
	@echo "$(C_RED)[philosophers OBJECTS && EXECUTABLES DELETED!]$(C_RES)"

re : fclean all
