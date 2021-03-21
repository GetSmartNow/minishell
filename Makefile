# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/09 17:56:31 by ctycho            #+#    #+#              #
#    Updated: 2021/03/21 13:57:04 by ctycho           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell

#flags------------------------------------------------------------------------

CC		:=	gcc
FLAG	:=	-I.
RM		:=	rm -f
AR		:=	ar rc

#directories------------------------------------------------------------------

MAIN_D	:=	./main/
LIB_D	:=	./libft/
GNL_D	:=	./get_next_line/
BUILT	:=	./builtins/
ENV		:=	./env/
TOOL	:=	./tools/
INC_D	:=	./include/

#files------------------------------------------------------------------------

INC		:=	minishell.h
SRCS	:=	$(addprefix ${MAIN_D}, main_test.c bin.c mini_pipes.c signal.c) \
			$(addprefix ${TOOL}, libft_utils.c ft_error.c mini_utils.c) \
			$(addprefix $(ENV), ft_shlvl.c ft_pwd.c) \
			$(addprefix ${BUILT}, mini_cd.c mini_echo.c mini_env.c mini_exit.c \
			mini_export.c mini_pwd.c mini_unset.c) parser.c new_split.c parser2.c

#colors----------------------------------------------------------------------

GREEN	:=	\033[0;32m
CYAN	:=	\033[0;36m
MAGENTA	:=	\033[0;35m
LGREEN	:=	\033[1;32m
LYELLOW	:=	\033[1;33m
LRED	:=	\033[1;31m
LBLUE	:=	\033[1;34m	

#rules------------------------------------------------------------------------

all:		$(NAME)
	
${NAME}: $(SRCS) $(INC) $(LIB_D)
	@make -C $(LIB_D)
	@$(CC) -o $(NAME) $(SRCS) $(LIB_D)libft.a $(FLAG)
	@echo "${CYAN}Library "${NAME}" succesfully compiled"

clean:	
	@make clean -C $(LIB_D)
	@echo "${LGREEN}Everything is cleaned succesfully"

fclean:
	@rm -f ${NAME}
	@make fclean -C $(LIB_D)
	@echo "${LGREEN}Everything is cleaned succesfully"
	@cd $(LIB_D) && make fclean

re:			fclean all
	@echo "${LBLUE}Library successfuly rebuilt"
