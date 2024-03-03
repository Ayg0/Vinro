NAME = vinro

CC = gcc 

CFLAGS= -Werror -Wall -Wextra -g -lcurses

SRCS = main.c outputHelper.c inputHelper.c fileManipulation.c

OBJS = ${SRCS:.c=.o}

RM = rm -f

all: $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re