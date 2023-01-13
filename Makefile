NAME = vinro
SRC = main.cpp
OBJ = ${SRC:.cpp=.o}
CPPFLAGS = -Wall -Wextra -Werror

all:	$(NAME)

$(NAME):	$(OBJ)
		c++ $(OBJ) $(CPPFLAGS) -o $(NAME)
clean:
	rm -rf $(OBJ)
fclean:	clean
	rm -rf $(NAME)
re:	fclean all

.PHONY: clean fclean re all