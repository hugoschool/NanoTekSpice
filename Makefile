CXX	:=	clang++
CXXFLAGS	:=	-Wall -Wextra -std=c++20
CPPFLAGS	:=	-I include

SRC	:=	src/main.cpp \
		src/Circuit.cpp \
		src/Factory.cpp \
		src/Tristate.cpp \
		src/components/AComponent.cpp \
		src/components/AndComponent.cpp \
		src/components/ClockComponent.cpp \
		src/components/FalseComponent.cpp \
		src/components/InputComponent.cpp \
		src/components/NotComponent.cpp \
		src/components/OrComponent.cpp \
		src/components/OutputComponent.cpp \
		src/components/TrueComponent.cpp \
		src/components/XorComponent.cpp
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
