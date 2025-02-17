NAME	=	philo

SRC	=	dinner.c init.c monitoring.c safe_functions.c utils.c getters_setters.c main.c parsing.c synchro_utils.c write.c

OBJ	=	${SRC:.c=.o}

CC	=	cc

CFLAGS	=  -g -Wall -Wextra -Werror -pthread -fsanitize=thread

############# COLOR ##################

GREEN	=	\033[0;32m

RED	=	\033[0;31m

BLUE	=	\033[0;34m

END	=	\033[0m

#####################################

all:	$(NAME) ${OBJ}

.c.o:
	@${CC} ${CFLAGS} $< -c -o $@
	@echo "${BLUE}OBJECTS CREATED!!!${END}"

$(NAME): ${OBJ}
	@${CC} ${CFLAGS} ${OBJ} -o $(NAME) -lpthread
	@echo "${GREEN}Let's go, philosophers!!${END}"

clean:
	@rm -rf ${OBJ}
	@echo "${RED}Cleaning....!!${END}"

fclean:	clean
	@rm -rf $(NAME)

re: fclean all