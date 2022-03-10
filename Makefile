NAME = minirt

all :
	gcc ./srcs/Lib/*.c ./srcs/parse/*.c ./srcs/*.c  -I ./includes -lmlx -framework OpenGL -framework Appkit -o $(NAME) 

clean :
	rm -rf $(NAME)

re	:
	clean all 
run : $(NAME)
	./$(NAME)
