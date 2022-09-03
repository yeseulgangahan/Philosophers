NAME		:= philo

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
RM			:= rm -f

ifdef DEBUG
	CFLAGS	+=	-g
endif

SRCS	:= \
				main.c

OBJS		= $(SRCS:.c=.o)

.PHONY:			all debug clean fclean re

all:			$(NAME)

debug:			
				$(MAKE) DEBUG=true

clean:
				$(RM) $(OBJS) $(OBJS_BONUS)

fclean:			clean
				$(RM) $(NAME) $(NAME_BONUS)

re:				fclean all

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $^ -o $@