NAME := minirt
SRCS_DIR := ./srcs
INC_DIR := ./includes
OBJ_DIR := ./objs
SRCS := $(shell find $(SRCS_DIR) -name '*.c')
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CC := gcc
CFLAGS := -Wall -Werror -Wextra -finline-functions -Ofast -fno-strict-aliasing -ffast-math

all: $(OBJS) $(NAME)
	@echo "Minirt ready to use: Usage - ./minirt scenes/___.rt"

${OBJ_DIR}/%.o:%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $^ -I${INC_DIR}

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework Appkit $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS) $(OBJ_DIR)

fclean: clean 
	@rm -rf $(NAME)

re: fclean all 

.PHONY: all clean fclean re
