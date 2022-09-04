NAME		:= philo

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
RM			:= rm -f

ifdef DEBUG
	CFLAGS	+=	-g
endif

SRCS	:= \
				main.c \
				init.c \
				utils.c

OBJS		= $(SRCS:.c=.o)

.PHONY:			all de clean fclean re

all:			$(NAME)

de:			
				$(MAKE) DEBUG=true

clean:
				$(RM) $(OBJS) $(OBJS_BONUS)

fclean:			clean
				$(RM) $(NAME) $(NAME_BONUS)

re:				fclean all

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $^ -o $@