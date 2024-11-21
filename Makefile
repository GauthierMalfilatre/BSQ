##
## EPITECH PROJECT, 2024
## DAMIEN
## File description:
## Makefile
##

SRC =	src/main_it.c \
		src/utils/my_getnbr.c

OBJ = $(SRC:.c=.o)

NAME = setting_up

CFLAGS = -Wall

TD ?= TESTS/

TFLAGS ?= -a

all: $(NAME)

$(NAME): $(OBj)
	gcc -Ofast -g -w -o $(NAME) $(SRC)

it: fclean
	rm -f bsq_it
	gcc -g -Ofast -o bsq_it src/utils/my_getnbr.c src/main_it.c

run: all
	./$(NAME) | cat -e

debug:	all
	valgrind ./$(NAME)

clean:
	find . -name "*~" -delete -o -name "#*#" -delete -o -name "*.out" -delete
	find . -name "*.o" -delete -o -name "unit_tests"  -delete
	find . -name "*.a" -delete -o -name "*.log" -o -name "'#*#'" -delete
	find . -name "*.gcda" -delete -o -name "*.gcno" -delete

fclean:
	rm -f $(NAME)
	make clean

code: fclean
	coding-style src .
	cat coding-style-reports.log
	rm -f coding-style-reports.log

tests_run: re
	gcc -w -o unit_test tests/*.c --coverage -lcriterion -L. -lmy
	./unit_test
	make fclean > /dev/null
	rm unit_test > /dev/null

test:
	make re > /dev/null
	rm -f lsres mylsres
	./$(NAME) $(TFLAGS) $(TD) >> mylsres
	ls $(TFLAGS) $(TD) >> lsres
	diff lsres mylsres

push:
	make fclean
	git add .
	@echo "What did you change ?" ; read COMMIT ; git commit -m "$$COMMIT"
	git push -u origin main

re: fclean all

kronk:
	@echo "Oh ouais."
