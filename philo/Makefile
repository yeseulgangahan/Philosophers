# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 09:53:06 by yehan             #+#    #+#              #
#    Updated: 2022/09/16 18:39:27 by yehan            ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
RM			:= rm -f

ifdef DEBUG
	CFLAGS	+=	-g
endif

ifdef ADDRESS
	CFLAGS	+=	-fsanitize=address
endif

ifdef THREAD
	CFLAGS	+=	-fsanitize=thread
endif

SRCS	:= \
				main.c \
				init.c \
				init2.c \
				philo.c \
				philo2.c \
				monitor.c \
				free.c \
				utils.c \

OBJS		= $(SRCS:.c=.o)

.PHONY:			all g th ad clean fclean re

all:			$(NAME)

g:				fclean
				$(MAKE) DEBUG=true

th:				fclean
				$(MAKE) THREAD=true

ad:				fclean
				$(MAKE) ADDRESS=true

clean:
				$(RM) $(OBJS) $(OBJS_BONUS)

fclean:			clean
				$(RM) $(NAME) $(NAME_BONUS)

re:				fclean all

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $^ -o $@