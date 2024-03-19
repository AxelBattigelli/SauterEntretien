##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## make 
##

SRC	=	src/main.c 					\
		src/my_str_to_word_array.c	\


OBJ = $(SRC:.c=.o)

CPPFLAGS += -I ./include
CFLAGS += -g -gdwarf-4 #-fsanitize=address,undefined
export CFLAGS

NAME = test

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) -g -gdwarf-4 $(OBJ) $(LIBS)

tests_run:
	$(CC) -Dmain=my_main -o unit-tests $(SRC) ./tests/tests.c $(CPPFLAGS) \
	$(LIBS) --coverage -lcriterion $(LDFLAGS) -g
	./unit-tests

clean:
	find -name '*.o' -delete

fclean: clean
	rm -f $(NAME)
	rm -f unit-tests*

re: fclean all
