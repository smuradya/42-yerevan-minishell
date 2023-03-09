NAME1		= minishell
SRCS		= $(shell find ./mandatory -name "*.c")
OBJS		= ${SRCS:.c=.o}
CC			= cc
LFLAGS      = -L./read_line_for/lib -lreadline
INCLUDES	= ./includes
CFLAGS		= -Wall -Werror -Wextra -I./read_line_for/include  -fsanitize=address -g
RD 			= ${shell find ${HOME} -name read_line_for 2>/dev/null}
RM			= rm -f

.c.o :
	@${CC} ${CFLAGS} -I $(INCLUDES) -c $< -o ${<:.c=.o}

all : $(NAME1)

$(NAME1) : ${OBJS}
	@$(CC) $(CFLAGS) $(LFLAGS) -I $(INCLUDES) -o $(NAME1) ${OBJS}

clean :
	@${RM} ${OBJS}

fclean : clean
	@${RM} ${NAME1}

install:
	cd readline-master && make clean && ./configure --prefix=${RD} && make && make install

re : fclean all

.PHONY : all clean fclean re