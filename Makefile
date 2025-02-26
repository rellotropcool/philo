
# Program name
NAME = philo

# Colors
DEFAULT    = \033[0m
BLACK    = \033[0;30m
RED        = \033[0;31m
GREEN    = \033[0;32m
YELLOW    = \033[0;33m
BLUE    = \033[0;34m
PURPLE    = \033[0;35m
CYAN    = \033[0;36m
BWHITE    = \033[1;37m

# Directories
SRCS_DIR = srcs
INCS_DIR = inc
OBJS_DIR = objs

# Files


define INCLUDES :=
	$(INCS_DIR)
endef
INCLUDES := $(strip $(INCLUDES))

define SRC :=
	data_init.c \
	dinner.c \
	get_set.c \
	main.c \
	monitor.c \
	parsing.c \
	synchro_utils.c \
	utils.c \
	write.c
endef
SRC := $(strip $(SRC))

OBJ := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRC))

# Utils
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
INCLUDES_FLAGS := $(addprefix -I , $(INCLUDES))

# Rules
all: $(NAME)

$(NAME): $(OBJ) $(BONUS)
	@echo "$(GREEN)* Assembling $(BWHITE)$@$(DEFAULT)"
	@$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@echo "$(CYAN)- Compiling$(DEFAULT) $<"
	@mkdir -p $(OBJS_DIR)/$(BONUS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES_FLAGS) -c $< -o $@

clean:
	@echo "$(RED)! Removing$(DEFAULT) ${OBJS_DIR} files"
	@${RM} ${OBJS_DIR}

fclean: clean
	@echo "$(RED)! Removing$(DEFAULT) $(NAME)"
	@$(RM) $(NAME)

re: fclean all