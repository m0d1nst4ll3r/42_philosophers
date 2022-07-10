# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/10 16:01:37 by rpohlen           #+#    #+#              #
#    Updated: 2022/07/10 16:07:21 by rpohlen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= $(addprefix src/, \
			  main.c \
			  init.c \
			  exit.c \
			  params.c \
			  time.c \
			  threads.c \
			  philo.c \
			  monitor.c)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinclude -pthread

NAME		= philo

OBJS		= $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

all:		$(NAME)

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
