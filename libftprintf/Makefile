
NAME	=	libftprintf.a

C_DIR	=	src

O_DIR	=	obj

SRCS	=	${patsubst %, ${C_DIR}/%, ${C_FILES}}

C_FILES	=	conv_spe_c.c	\
			conv_spe_d.c	\
			conv_spe_p.c	\
			conv_spe_prct.c	\
			conv_spe_s.c	\
			conv_spe_u.c	\
			conv_spe_x.c	\
			handle_var.c	\
			printf_parser.c	\
			ft_printf.c

OBJS	=	${patsubst ${C_DIR}/%, ${O_DIR}/%, ${SRCS:.c=.o}}

CC		=	clang

CFLAGS	=	-I. -Wall -Wextra -Werror ${OPTFLAG}

OPTFLAG	=	${OPTFLAG_CLI}

all:		${NAME}

${NAME}:	${OBJS}
			${MAKE} -C libft OPTFLAG_CLI="${OPTFLAG}"
			ar rcT ${NAME} ${OBJS} libft/libft.a

${O_DIR}/%.o : ${C_DIR}/%.c
			@mkdir -p obj
			${CC} ${CFLAGS} -c $< -o $@

.PHONY:		clean fclean re .c.o all

clean:
			rm -rf ${O_DIR}
			${MAKE} -C libft clean

fclean:		clean
			rm -f ${NAME}
			${MAKE} -C libft fclean

re:			fclean all     