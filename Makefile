NAME := minirt
SRCS_DIR := ./srcs
INC_DIR := ./includes
OBJ_DIR := ./objs
SRCS := main.c \
		lib/ft_split.c \
		lib/gnl.c \
		lib/ft_strlen.c \
		parse/parse_file.c \
		parse/parse_line.c \
		parse/parsers.c
SRCS_MADATORY := control.c hook.c
SRCS_BONUS 	:= controls_bonus.c hook_bonus.c
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
OBJS_MANDATORY := $(addprefix ${OBJ_DIR}/, $(SRCS_MADATORY:.c=.o))
OBJS_BONUS := $(addprefix ${OBJ_DIR}/, $(SRCS_BONUS:.c=.o))

CC := gcc
CFLAGS := -Wall -Wextra -Werror \
					-Ofast -fno-strict-aliasing \
					-fomit-frame-pointer -mtune=native \
					-msse4.2 -mfpmath=sse -march=native \
					-funsafe-math-optimizations -funroll-loops \
					-ffast-math -flto -finline-functions

all: OBJS += $(OBJS_MANDATORY)
all: OBJS_UNUSED := $(OBJS_BONUS)
all: $(OBJS_MANDATORY) $(NAME)
	@echo "Minirt ready to use: Usage - ./minirt scenes/___.rt"

bonus: OBJS += $(OBJS_BONUS)
bonus: OBJS_UNUSED := $(OBJS_MANDATORY)
bonus: $(OBJS_BONUS) $(NAME)
	@echo "Minirt ready to use: Usage - ./minirt scenes/___.rt | Move using LSHIFT SPACE W S A D"

${OBJ_DIR}/%.o: ${SRCS_DIR}/%.c
	@rm -rf $(NAME) $(OBJS_UNUSED)
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
