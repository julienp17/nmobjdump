##
## EPITECH PROJECT, 2021
## objdump
## File description:
## Makefile
##

CC			=	gcc

MAIN		=	$(addprefix $(SRC_D), main.c)

SRC			=	$(addprefix $(SRC_D), $(SRC_F))
OBJ			=	$(MAIN:.c=.o) $(SRC:.c=.o)
SRC_D		=	src/
SRC_F		=

UT_SRC		=	$(addprefix $(UT_SRC_D), $(UT_SRC_F))
UT_OBJ		=	$(UT_SRC:.c=.o)
UT_SRC_D	=	tests/
UT_SRC_F	=

CFLAGS		=	-W -Wall -Wextra -Werror $(INC) $(LDFLAGS)

INC			=	-I./inc

LDFLAGS		=

LDFLAGS_UT  =	-lcriterion --coverage

DBFLAGS		=	-g -g3 -ggdb

BIN			=	my_objdump

UT_BIN		=	unit_tests

RM			=	rm -f

all: $(BIN)

.PHONY: all
$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)
	cp $(BIN) ..

.PHONY: debug
debug: $(OBJ)
	$(CC) $(CFLAGS) $(DBFLAGS) -o $(BIN) $(OBJ)

.PHONY: tests_run
tests_run: clean $(OBJ) $(OBJ_UT)
	$(CC) $(CFLAGS) $(LDFLAGS_UT) -o $(BIN_UT) $(OBJ) $(OBJ_UT)
	./$(BIN_UT)

.PHONY: coverage
coverage:
	gcovr -b --exclude-directories tests
	gcovr -r . --exclude-directories tests

.PHONY: clean
clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_UT)
	$(RM) *.o
	$(RM) *.gc*

.PHONY: fclean
fclean: clean
	$(RM) $(BIN)
	$(RM) $(BIN_UT)

.PHONY: re
re: fclean all