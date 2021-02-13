# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/09 17:56:31 by ctycho            #+#    #+#              #
#    Updated: 2021/02/12 15:52:07 by ctycho           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

#flags------------------------------------------------------------------------

CC		=	gcc
FLAG	=	-Wall -Wextra -Werror
RM		=	rm -f
AR		=	ar rc


SRC_D	=	./src/
LIB_D	=	./libft/
GNL_D	=	./get_next_line/
OBJ_D	=	./obj

INC_D	=	./include/

#files------------------------------------------------------------------------

INC		=	minishell.h
SRCS	=	main_test.c bin.c

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
	
${NAME}: $(SRCS) ${INC}
	@$(CC) -o $(NAME) $(SRCS) $(LIB_D)libft.a $(GNL_D)gnl.a
	@echo "${CYAN}Library "${NAME}" succesfully compiled"

clean:		
	@rm -f ${NAME}
	@echo "${LGREEN}Everything is cleaned succesfully"

fclean:
	@rm -f ${NAME}
	@echo "${LGREEN}Everything is cleaned succesfully"

re:			fclean all
	@echo "${LBLUE}Library successfuly rebuilt"
