# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguerrer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/25 17:17:12 by aguerrer          #+#    #+#              #
#    Updated: 2021/06/25 18:05:11 by aguerrer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER = server
NAME_CLIENT = client
NAME = minitalk

CFLAGS = -Wall -Wextra -Werror
CC = gcc
RM = rm -f

SRCDIR = ./src/

SRCNAME_UTILS = ft_atoi.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			get_next_line.c \
			get_next_line_utils.c

INCLUDES = -I ./includes/

SRCS_UTILS = ${addprefix ${SRCDIR}, ${SRCNAME_UTILS}}
SRC_SERVER = ./src/server.c
SRC_CLIENT = ./src/client.c

OBJS_UTILS = $(SRCS_UTILS:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

all : $(NAME)

$(NAME) : $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER) : $(OBJS_UTILS) $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

$(NAME_CLIENT) : $(OBJS_UTILS) $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

bonus : all

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean :
	$(RM) $(OBJS_UTILS) $(OBJ_SERVER) $(OBJ_CLIENT) 

fclean : clean
	$(RM) $(NAME_SERVER) $(NAME_CLIENT)

re : fclean all
