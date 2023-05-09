name = vinro

CC = c++

CPPFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

SRC = main.cpp term_helpers.cpp file_helpers.cpp general.cpp

OBJ = ${SRC:.cpp=.o} 

all: $(name)

$(name): $(OBJ)
		$(CC) $(CPPFLAGS) -lncurses $(OBJ) -o $(name)

clean:
		rm -rf $(OBJ)
fclean: clean
		rm -rf $(name)
re:		fclean all
.PHONY: all clean fclean re