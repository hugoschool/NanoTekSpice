CXX	:=	clang++
CXXFLAGS	:=	-Wall -Wextra -std=c++20

SRC	:=	src/main.cpp
OBJ	:=	$(SRC:.cpp=.o)

BINARY	:=	nanotekspice

all:	$(BINARY)

$(BINARY):	$(OBJ)
	$(CXX) -o $(BINARY) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(BINARY)

re:	fclean all

.PHONY:	all clean fclean re
