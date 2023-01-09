NAME = philosopher

NAMEB = philosopher_bonus

LIBS_PERSO = libft/libft.a

SRCS =  main.c 			\
		parsing.c 		\
		philofactory.c	\
		routine.c 		\
		ft_isdigit.c 	\
		ft_putnbr_fd.c 	\
		ft_putstr_fd.c  \
		triche.c

BNS =

OBJS = ${SRCS:.c=.o}

VERIF = -Wall -Wextra -Werror -ggdb3

CC = gcc
RM = rm -f

all: ${NAME}

%.o: %.c incl/philosopher.h
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(VERIF) $(OBJS) -o $(NAME)

clean:
	${RM} ${OBJS} ${OBJSB}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all clean libs bonus fclean re