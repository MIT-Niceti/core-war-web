NAME		=	compiler

CXX		=	g++

RM		=	rm -f

SRCS		=	main.cpp	\
			Compiler.cpp	\
			Tokenizer.cpp	\
			Token.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	+=	-W -Wall -Werror -Wextra -std=c++11


all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) $(OBJS) -o $(NAME) $(CPPFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
