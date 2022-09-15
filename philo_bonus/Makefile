# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 09:53:01 by yehan             #+#    #+#              #
#    Updated: 2022/09/15 09:46:50 by yehan            ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME		:= philo_bonus

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
				main_bonus.c \
				init_bonus.c \
				init2_bonus.c \
				philo_bonus.c \
				philo2_bonus.c \
				monitor_bonus.c \
				free_bonus.c \
				utils_bonus.c \

OBJS		= $(SRCS:.c=.o)

.PHONY:			all g th clean fclean re

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
