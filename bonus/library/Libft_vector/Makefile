# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 07:53:55 by dkim2             #+#    #+#              #
#    Updated: 2022/08/10 14:55:13 by yunselee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES: .c .o

NAME = libvector.a
NAME_DYN = libvector_dny.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -O2

AR = ar
ARFLAGS = -rs

SRCS = vector3_1.c vector3_2.c \
		quaternion_1.c quaternion_2.c \
		matrix33.c transform.c
OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

all : $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $^

clean :
	rm -rf $(OBJS) $(B_OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re