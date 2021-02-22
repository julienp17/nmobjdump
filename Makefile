##
## EPITECH PROJECT, 2021
## nmobjdump [WSL: Ubuntu-20.04]
## File description:
## Makefile
##

MAKE_NM			=	make -C ./nm
MAKE_OBJDUMP	=	make -C ./objdump

all:
	$(MAKE_NM) all
	$(MAKE_OBJDUMP) all

nm:
	$(MAKE_NM) all

objdump:
	$(MAKE_OBJDUMP) all

tests_run: clean
	$(MAKE_NM) tests_run
	cp ./nm/*.gc* .
	$(MAKE_OBJDUMP) tests_run
	cp ./objdump/*.gc* .

clean:
	$(MAKE_NM) clean
	$(MAKE_OBJDUMP) clean

fclean: clean
	$(MAKE_NM) fclean
	$(MAKE_OBJDUMP) fclean

re: fclean all