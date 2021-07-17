### colors ###
RESET = \033[0m
BOLD = \033[1m
RED = \033[31m
GREEN = \033[32m
GRAY = \033[2m
#########

NAME = philo_one

CC = gcc
SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = includes/

SRC_FILES = create_args.c \
			create_str_from_time.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_free.c \
			ft_itoa.c \
			ft_memcpy.c \
			ft_strlen.c \
			init.c \
			init_utilc.c \
			main.c \
			philosophers.c \
			philosophy_of_action2.c \
			philosophy_of_action.c

OBJ_FILES = $(SRC_FILES:.c=.o)
DEP_FILES = $(SRC_FILES:.c=.d)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
DEP = $(addprefix $(OBJ_DIR), $(DEP_FILES))

INC = $(addprefix -I, $(INC_DIR)) 
CFLAGS = -Wall -Werror -Wextra -pthread

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $^ -o $@ 
	@echo "$(GREEN)$(BOLD)$(NAME) created!$(RESET)"

-include $(DEP)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(INC) $(CFLAGS) -c $< -o $@ -MMD

clean:
	@echo "$(GRAY)Deleting...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)$(BOLD)Object files deleted!$(RESET)$(RED)$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)$(BOLD)$(NAME) deleted!$(RESET)"

re: fclean all

.PHONY: all clean fclean re 
