# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbarbry <kbarbry@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/30 00:52:12 by kbarbry           #+#    #+#              #
#    Updated: 2021/12/02 04:24:34 by kbarbry          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET		=	\033[0m
BPurple		=	\033[1;35m
BGreen		=	\033[1;32m
UYellow		=	\033[3;33m
UGreen		=	\033[3;32m
BlBlue		=	\033[1;96m
Red			=	\033[0;31m

PART_1		=	mandatory/main.c \
				mandatory/pipex.c

UTILITIES	=	utilities/parsing_path.c \
				utilities/utilities.c \
				utilities/ft_split.c \
				utilities/get_next_line.c

BONUS		=	bonus/main_bonus.c \
				bonus/pipex_bonus.c

N			=	"\n"

OBJ			=	${PART_1:.c=.o} \
				${UTILITIES:.c=.o}

OBJ_BONUS	=	${BONUS:.c=.o} \
				${UTILITIES:.c=.o}

CC			=	gcc
FLAGS		=	-Wall -Werror -Wextra -I.
NAME		=	pipex

all:		${NAME}

${N}:
	@echo "\n====================================================="
	@echo "\033[12G  ____  __  ____  ____  _  _ "
	@echo "\033[12G (  _ \(  )(  _ \(  __)( \/ )"
	@echo "\033[12G  ) __/ )(  ) __/ ) _)  )  ( "
	@echo "\033[12G (__)  (__)(__)  (____)(_/\_)\n"

%.o:%.c pipex.h
	@echo "${BPurple}[OBJ_FILE CREATED] :${RESET} ${<:.c=.o}${BGreen}\033[50G[✔]${RESET}"
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:	 ${N} ${OBJ}
	@echo "${BlBlue}\nExecutable file :${RESET} ./${NAME}\n"
	@${CC} ${FLAGS} -o ${NAME} ${OBJ}
	@echo "====================> ${UGreen}Mandatory${RESET} <====================\n"

bonus:	 ${N} ${OBJ_BONUS}
	@echo "${BlBlue}\nExecutable file :${RESET} ./${NAME}\n"
	@${CC} ${FLAGS} -o ${NAME} ${OBJ_BONUS}
	@echo "======================> ${UYellow}Bonus${RESET} <======================\n"

clean:
	@echo "${Red}\nClean : Deleting objects...${RESET}\n"
	@rm -f ${OBJ} ${OBJ_BONUS}

fclean: clean
	@rm -f ${NAME}
	@echo "${Red}FClean : Deleting executable...${RESET}\n"

re:		fclean all

.PHONY: clean fclean all re