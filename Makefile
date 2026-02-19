CXX	:=	clang++
CXXFLAGS	:=	-Wall -Wextra -std=c++20
CPPFLAGS	:=	-I include

ifeq ($(ENV), dev)
	CXXFLAGS	+=	-g3
endif

SRC	:=	src/main.cpp \
		src/Circuit.cpp \
		src/Exception.cpp \
		src/Factory.cpp \
		src/NanoTekSpice.cpp \
		src/Parser.cpp \
		src/Shell.cpp \
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
		src/components/XorComponent.cpp	\
		src/components/NandComponent.cpp	\
		src/components/NorComponent.cpp	\
		src/components/gates/4001.cpp	\
		src/components/gates/4011.cpp	\
		src/components/gates/4030.cpp	\
		src/components/gates/4069.cpp	\
		src/components/gates/4071.cpp	\
		src/components/gates/4081.cpp	\
		src/components/advanced/4008.cpp	\
		src/components/advanced/4013.cpp	\
		src/components/advanced/FullBitAdder.cpp
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
