
ifeq (${HOSTTYPE},)
	HOSTTYPE = ${shell uname -m}_${shell uname -s}
endif

NAME	=	libft_malloc_${HOSTTYPE}.so

LN_NAME	=	libft_malloc.so

C_DIR	=	src

O_DIR	=	obj

SRCS	=	${patsubst %, ${C_DIR}/%, ${C_FILES}}

C_FILES	=	malloc.c\
			free.c\
			realloc.c\
			show_alloc_mem.c\
			libft_malloc.c\

OBJS	=	${patsubst ${C_DIR}/%, ${O_DIR}/%, ${SRCS:.c=.o}}

CC		=	clang

CFLAGS	=	-I. -fPIC ${OPTFLAG} # ${DBFLAGS}

# DBFLAGS	=	-ggdb -O0 -Wall -Wextra -Werror

OPTFLAG	=	${OPTFLAG_CLI}

all:		${NAME}

${NAME}:	${OBJS}
			${MAKE} -C libftprintf OPTFLAG_CLI="-fPIC ${OPTFLAG}"
			${CC} ${CFLAGS} -shared ${OBJS} -Wl,--whole-archive ./libftprintf/libftprintf.a -Wl,--no-whole-archive -o ${NAME}
			ln -fs ${NAME} ${LN_NAME}
			@echo "\033[0;32mmake ${NAME} DONE\033[0m"

test:		${NAME}
			${CC} ${CFLAGS} main.c ./${LN_NAME}

${O_DIR}/%.o : ${C_DIR}/%.c
			@mkdir -p obj
			${CC} ${CFLAGS} -c $< -o $@

.PHONY:		clean fclean re .c.o all

clean:
			rm -rf ${O_DIR}
			${MAKE} -C libftprintf clean
			@echo "\033[0;32mclean DONE\033[0m"

fclean:		clean
			rm -f ${NAME}
			rm -f ${LN_NAME}
			rm -f a.out
			${MAKE} -C libftprintf fclean
			@echo "\033[0;32mfclean DONE\033[0m"

re:			fclean all