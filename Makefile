NAME = game

CC = g++

SRCDIR = src
OBJDIR = obj

FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

RM = rm -rf

SRC = src/*.cpp

OBJ = obj/*.o

all: $(NAME)
	@echo "MAKE ALL IS DONE"

$(NAME):
	@mkdir -p $(OBJDIR)
	@$(CC) -c $(SRC)
	@mv *.o $(OBJDIR)
	@$(CC) $(OBJ) -o $(NAME) $(FLAGS)

clean:
	@$(RM) $(OBJDIR)
	@echo "MAKE CLEAN IS DONE"

fclean: clean
	@$(RM) $(NAME)
	@echo "MAKE FCLEAN IS DONE"

re: fclean all
	@echo "MAKE RE IS DONE"

.PHONY: clean fclean
