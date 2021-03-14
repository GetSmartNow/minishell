# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/31 11:32:38 by ctycho            #+#    #+#              #
#    Updated: 2021/03/14 11:08:23 by ctycho           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

#flags------------------------------------------------------------------------

CC		=	gcc
FLAG	=	-Wall -Wextra -Werror
RM		=	rm -f
AR		=	ar rc

#directories------------------------------------------------------------------

INC_D	:=	./include/
GNL_D	:=	./ft_gnl/
IS_D	:=	./ft_is/
LST_D	:=	./ft_lst/
MEM_D	:=	./ft_mem/
PUT_D	:=	./ft_put/
SKIP_D	:=	./ft_skip/
STR_D	:=	./ft_str/
TO_D	:=	./ft_to/

#files------------------------------------------------------------------------

INC		=	libft.h
SRCS	=	$(addprefix $(GNL_D), get_next_line.c get_next_line_utils.c) \
			$(addprefix $(IS_D), ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c) \
			$(addprefix $(LST_D), ft_lstnew.c ft_lstadd_front.c \
			ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ) \
			$(addprefix $(MEM_D), ft_memset.c ft_bzero.c ft_memcpy.c \
			ft_memccpy.c ft_memmove.c ft_memdel_1d.c \
			ft_memdel_2d.c ft_memdel_3d.c ft_memchr.c ft_memcmp.c \
			ft_calloc.c) \
			$(addprefix $(PUT_D), ft_putchar_fd.c \
			ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c) \
			$(addprefix $(SKIP_D), ) \
			$(addprefix $(STR_D), ft_intlen.c ft_strlen.c \
			ft_strlcpy.c ft_strlcat.c ft_strchr.c \
			ft_strrchr.c ft_strnstr.c ft_strcmp.c \
			ft_strncmp.c ft_strjoin.c ft_strtrim.c ft_split.c \
			ft_strdup.c ft_substr.c ft_strmapi.c) \
			$(addprefix $(TO_D), ft_atoi.c ft_toupper.c ft_tolower.c \
			ft_itoa.c)

OBJS	=	${SRCS:.c=.o}

#colors----------------------------------------------------------------------

GREEN	=	\033[0;32m
CYAN	=	\033[0;36m
MAGENTA	=	\033[0;35m
LGREEN	=	\033[1;32m
LYELLOW	=	\033[1;33m
LRED	=	\033[1;31m
LBLUE	=	\033[1;34m	

#rules------------------------------------------------------------------------

all:		$(NAME)
	
${NAME}: ${OBJS} ${INC_D}${INC}
	@${AR} ${NAME} ${OBJS}
	@ranlib ${NAME}
	@echo "${CYAN}Library "${NAME}" succesfully compiled"

%.o: %.c
	@${CC} ${FLAG} -I ${INC_D} -c $< -o $@
	@echo "${MAGENTA}Object file: ${LYELLOW}$@ ${GREEN}successfuly compiled"

clean:		
	@rm -f ${OBJS}
	@echo "${LRED}All object files were cleaned"

fclean:		clean
	@rm -f ${NAME}
	@echo "${LRED}Binary file was cleaned"
	@echo "${LGREEN}Everything is cleaned succesfully"

re:     fclean all
	@echo "${LBLUE}Library successfuly rebuilt"
