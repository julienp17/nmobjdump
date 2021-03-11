##
## EPITECH PROJECT, 2021
## nm
## File description:
## Makefile
##

CC			=	gcc

MAIN		=	$(addprefix $(SRC_D), main.c)
OBJ_M		=	$(MAIN:.c=.o)

SRC			=	$(addprefix $(SRC_D), $(SRC_F))
OBJ			=	$(SRC:.c=.o)
SRC_D		=	src/
SRC_F		=	nm.c \
				extract.c \
				dump.c \
				symbol_type.c \
				sort.c

UT_SRC		=	$(addprefix $(UT_SRC_D), $(UT_SRC_F))
UT_OBJ		=	$(UT_SRC:.c=.o)
UT_SRC_D	=	tests/
UT_SRC_F	=

CFLAGS		=	-W -Wall -Wextra -Werror $(INC) $(LDFLAGS)

INC			=	-I./inc

LDFLAGS		=

LDFLAGS_UT  =	-lcriterion --coverage

DBFLAGS		=	-g -g3 -ggdb

BIN			=	my_nm

UT_BIN		=	unit_tests

RM			=	rm -f

all: $(BIN)

.PHONY: all
$(BIN): $(OBJ_M) $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ_M) $(OBJ)
	cp $(BIN) ..

.PHONY: debug
debug: $(OBJ_M) $(OBJ)
	$(CC) $(CFLAGS) $(DBFLAGS) -o $(BIN) $(OBJ_M) $(OBJ)

.PHONY: tests_run
tests_run: clean $(OBJ) $(UT_OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS_UT) -o $(UT_BIN) $(OBJ) $(UT_OBJ)
	./$(UT_BIN)

.PHONY: functional_tests
functional_tests:
	./tests/functional/functional_tests.sh

.PHONY: coverage
coverage:
	gcovr -b --exclude-directories tests
	gcovr -r . --exclude-directories tests

.PHONY: clean
clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_M)
	$(RM) $(OBJ_UT)
	$(RM) *.o
	$(RM) *.gc*

.PHONY: fclean
fclean: clean
	$(RM) $(BIN)
	$(RM) $(BIN_UT)

.PHONY: re
re: fclean all