# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yilgar <yilgar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 10:58:15 by yilgar            #+#    #+#              #
#    Updated: 2025/03/06 21:40:47 by yilgar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus

MAKEFLAGS += --no-print-directory

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

SRC = srcs/pipex.c srcs/utils.c srcs/error.c lib/gnl/get_next_line.c lib/gnl/get_next_line_utils_bonus.c lib/gnl/get_next_line_bonus.c 
OBJS = $(SRC:.c=.o)


B_SRCS = bonus/pipex_bonus.c bonus/utils2_bonus.c bonus/utils_bonus.c bonus/pipex_bonus_lastpip.c bonus/pipex_bonus_midpip.c srcs/utils.c srcs/error.c lib/gnl/get_next_line_utils_bonus.c lib/gnl/get_next_line_bonus.c 
B_OBJS = $(B_SRCS:.c=.o)

HEADER = -Iheader

LIBFT_LIB = ./lib/libft/libft.a


.c.o:	%.o : %.c
	@gcc ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)


all: ${NAME}

${NAME}: ${OBJS}
	@echo "\033[33m----compiling lib---- \n"
	@echo "\n \033[0;32m✅ compiling libft completed!\033[0m"
	@make -C ./lib/libft
	@$(CC) ${OBJS} ./lib/libft/libft.a -o ${NAME}
	@echo "\n \033[0;32m✅ compiling get_next_line completed!\033[0m"
	@echo "\n \033[0;32m✅ pipex ready, compile completed!\033[0m"


bonus:	${NAME_BONUS}

${NAME_BONUS}: ${B_OBJS}
	@echo "\033[33m----Compiling lib----"
	@make -C ./lib/libft
	@echo "\n \033[0;32m✅ compiling bonus...!\033[0m"
	@$(CC) ${B_OBJS} ./lib/libft/libft.a -o ${NAME_BONUS}				

clean:
	@make clean -C ./lib/libft
	@${RM} ./lib/gnl/get_next_line.o
	@rm -f ${OBJS} ${B_OBJS}
	@echo "\n\033[0;31m🔥 .o files removed!\033[0m\n"
					
fclean: 	clean
	@make fclean -C ./lib/libft
	@${RM} ./lib/gnl/get_next_line.o
	@echo "\n\033[0;31m🔥 get_next_line removed!\033[0m\n"
	@${RM} pipex_bonus
	@rm -f $(NAME)
	@echo "\n\033[0;31m🔥 pipex & pipex_bonus removed!\033[0m\n"
	@echo "\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\n"


valgrind:
	@echo "\033[0;32m🚀 [✅ correct input]\033[0m"
	@echo "\n"
	@- valgrind --leak-check=full --show-leak-kinds=all ./pipex infile "cat" "grep test" a || true
	@echo "\n\033[0;31m⚡ [❌ wrong command input]\033[0m\n"
	@- valgrind --leak-check=full --show-leak-kinds=all ./pipex infile "ct" "grep test" a || true
	@echo "\n\033[0;31m⚡ [❌ wrong command2 input]\033[0m\n"
	@- valgrind --leak-check=full --show-leak-kinds=all ./pipex infile "ct" "grep test" a || true
	@echo "\n\033[0;33m🚨 [⚡ wrong infile input]\033[0m\n"
	@- valgrind --leak-check=full --show-leak-kinds=all ./pipex infil "cat" "grep test" a || true
	@echo "\n\033[0;33m🚨 [⚡ wrong outfile input]\033[0m\n"
	@- valgrind --leak-check=full --show-leak-kinds=all ./pipex infil "cat" "grep test"  || true
	@echo "\n\033[0;32m🎉 [✨ All Valgrind tests completed.]\033[0m\n"
	@- valgrind --leak-check=full --show-leak-kinds=all ./pipex infile "" "grep test"  || true
	@echo "\n\033[0;32m🎉 [✨ All Valgrind tests completed.]\033[0m\n"
	@- valgrind --leak-check=full --show-leak-kinds=all ./pipex infile "" ""  || true
	@echo "\n\033[0;32m🎉 [✨ All Valgrind tests completed.]\033[0m\n"
	@- valgrind --leak-check=full --show-leak-kinds=all ./pipex infile "cat" ""  || true
	@echo "\n\033[0;32m🎉 [✨ All Valgrind tests completed.]\033[0m\n"

re:	fclean all

re_bonus: fclean bonus


.PHONY: all clean fclean re bonus re_bonus valgrind valgrindpip valgrindcmd