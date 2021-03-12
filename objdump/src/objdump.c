/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu-20.04]
** File description:
** objdump
*/

#include "my_objdump.h"

int objdump(const char *filename)
{
    elf_t *elf = extract_elf(filename);

    if (elf == NULL)
        return 1;
    dump(elf);
    return 0;
}