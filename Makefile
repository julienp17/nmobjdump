##
## EPITECH PROJECT, 2021
## nmobjdump [WSL: Ubuntu-20.04]
## File description:
## Makefile
##

$@

RULES = objdump nm

all: $(RULES)

$(RULES):
	make -C $@

fclean:
	make -C objdump $@
	make -C nm $@
	rm -f my_nm
	rm -f my_objdump

all clean re:
	make -C objdump $@
	make -C nm $@

.PHONY: $(RULES)