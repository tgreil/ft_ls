# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/07 16:24:07 by tgreil            #+#    #+#              #
#    Updated: 2018/06/30 15:35:31 by tgreil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main_ls.c			\
			param_handler.c		\
			option.c			\
			list_manag.c		\
			print_result.c		\
			ft_ls_apply.c		\
			sort.c				\
			ls_utils.c

OBJS	= $(addprefix srcs/, $(SRCS:.c=.o))

LIBS	= -Llibft/ -lft

NAME	= ft_ls

RM	= rm -f

CC	= gcc

MAKELIB	= make -C libft/

LIB	= libft/libft.a

CFLAGS	= -W -Wall -Wextra -Werror
CFLAGS	+= -Iincludes/ -Ilibft/includes/

LDFLAGS	=  $(LIBS)

$(NAME): $(LIB)	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(LIB):
	$(MAKELIB)

all:	$(NAME)

clean:
	$(RM) $(OBJS)
	$(MAKELIB) clean

fclean:
	$(RM) $(OBJS)
	$(MAKELIB) fclean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	re fclean clean all $(PROJECT)
