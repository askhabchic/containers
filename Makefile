NAME = test

#SRC = stack_main.cpp
SRC = main_test_vector.cpp

HEADER = $(wildcard *.hpp)

FLAGS = -Wall -Werror -Wextra -std=c++98

OBJ = $(SRC:.cpp=.o)

all: $(NAME)
$(NAME): $(OBJ) $(HEADER) 
	@clang++ $(OBJ) $(FLAGS) -o $(NAME) -g
%.o:%.cpp $(HEADER)
	@clang++ $(FLAGS) -c $< -o $(<:.cpp=.o) -g
clean: 
	@rm -f $(OBJ)
fclean: clean
	@rm -f $(NAME)
re: fclean all

run: 
	@./$(NAME)

rerun: re 
	@./$(NAME)

leak:
	MallocStackLogging=1 MallocScribble=1 leaks -atExit -- ./$(NAME)

.PHONY: clean fclean re run rerun
