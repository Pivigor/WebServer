SRCS		=	main.cpp						\
				Web/SocketClient.cpp			\
				Web/SocketServer.cpp			\
				Web/WebClient.cpp				\
				Web/WebServer.cpp				\
				Http/HttpRequest.cpp			\
				Http/HttpRequestParams.cpp		\
				Http/HttpHeaders.cpp			\
				Http/HttpResponse.cpp			\
				Config/Parser.cpp				\
				Config/ConfigServer.cpp			\
				Config/LocationInfo.cpp			\
				Tools/FileReader.cpp			\
				Tools/Helper.cpp				\
				Tools/CGI.cpp
OBJS		= ${SRCS:.cpp=.o}
DEPS		= ${SRCS:.cpp=.d}
NAME		= webserv
CC			= clang++
CFLAGS		= -Wall -Wextra -Werror -std=c++98
DEPFLAGS	= -MMD -MF ${<:.cpp=.d}
RM			= rm -f

all:		${NAME}

$(NAME):	${OBJS}
			${CC} -o ${NAME} ${OBJS}

-include ${DEPS}

%.o:		%.cpp
			${CC} ${CFLAGS} -c $< -o $@ ${DEPFLAGS} -I .

clean:
			${RM} ${OBJS} ${DEPS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
