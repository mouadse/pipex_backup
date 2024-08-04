NAME        := pipex
BONUS_NAME  := pipex_bonus
CC          := gcc
FLAGS       := -Wall -Wextra -Werror
SRCS        := memory_management.c \
               error_handling.c \
               libft_utils3.c \
               libft_utils2.c \
               pipex_parser.c \
               get_next_line/get_next_line_utils.c \
               get_next_line/get_next_line.c \
               heredoc_handler.c \
               execution.c \
               process_management.c \
               libft_utils1.c \
               pipeline_init.c \
               pipeline_init_bonus.c
MAIN        := main.c
BONUS_MAIN  := main_bonus.c
OBJS        := $(SRCS:.c=.o)
MAIN_OBJ    := $(MAIN:.c=.o)
BONUS_OBJ   := $(BONUS_MAIN:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

CLR_RMV     := \033[0m
RED         := \033[1;31m
GREEN       := \033[1;32m
YELLOW      := \033[1;33m
BLUE        := \033[1;34m
CYAN        := \033[1;36m
RM          := rm -f

${NAME}: ${OBJS} ${MAIN_OBJ}
	@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
	${CC} ${FLAGS} -o ${NAME} ${OBJS} ${MAIN_OBJ}
	@echo "$(GREEN)$(NAME) created ✔️"

all: ${NAME}

${BONUS_NAME}: ${OBJS} ${BONUS_OBJ}
	@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(BONUS_NAME) ${CLR_RMV}..."
	${CC} ${FLAGS} -o ${BONUS_NAME} ${OBJS} ${BONUS_OBJ}
	@echo "$(GREEN)$(BONUS_NAME) created ✔️"

bonus: ${BONUS_NAME}

clean:
	@ ${RM} *.o */*.o */*/*.o
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean: clean
	@ ${RM} ${NAME} ${BONUS_NAME}
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
	@ echo "$(RED)Deleting $(CYAN)$(BONUS_NAME) $(CLR_RMV)binary ✔️"

re: fclean all

.PHONY: all bonus clean fclean re

