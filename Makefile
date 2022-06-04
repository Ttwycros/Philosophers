NAME =	philosophers

CC =	cc
CFLAGS =	-g -Werror -Wextra -Wall -MMD -pthread

RM =	rm -rf

SRC =		Main.c\
			Init.c\
			Philosopher_actions.c\
			General_utils.c\
			Errors.c\
			Game.c\
			Time_utils.c\

INCLUDE =	-I Philosophers.h\

OBJ =	$(SRC:.c=.o)
D =		$(SRC:.c=.d)

.PHONY :	all clean re fclean

.c.o :		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

$(NAME):	$(OBJ) Makefile
				${CC} ${CFLAGS} ${LD_FLAGS} ${OBJ} -o ${NAME}

all:	$(NAME)

clean:
				$(RM) $(OBJ) $(D)

fclean:		clean
				$(RM) $(NAME)

re:			fclean all

-include $(D)