# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/07 16:24:07 by tgreil            #+#    #+#              #
#    Updated: 2018/06/25 11:25:36 by tgreil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main_ls.c			\
			param_handler.c		\
			option.c			\
			list_manag.c

OBJS	= $(addprefix srcs/, $(SRCS:.c=.o))

LIBS	= -Llibft/ -lft

PROJECT = ft_ls_project

NAME	= ft_ls

RM	= rm -f

CC	= gcc

MAKELIB	= make -C libft/

LIB	= libft/libft.a

CFLAGS	= -W -Wall -Wextra -Werror
CFLAGS	+= -Iincludes/ -Ilibft/includes/

LDFLAGS	=  $(LIBS)

$(PROJECT):	$(LIB) $(NAME)

$(NAME): 	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(LIB):
	$(MAKELIB)

all:	$(PROJECT)

clean:
	$(RM) $(OBJS)
	$(MAKELIB) clean

fclean:
	$(RM) $(OBJS)
	$(MAKELIB) fclean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	re fclean clean all $(PROJECT)
