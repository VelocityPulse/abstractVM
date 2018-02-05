.PHONY: all clean fclean re

CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = avm
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME) 

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -fv $(OBJ)

fclean: clean
	@rm -fv $(NAME)

re: fclean all
