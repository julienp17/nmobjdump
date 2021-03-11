/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu-20.04]
** File description:
** nm
*/

#include "my_nm.h"

int nm(const char *filename)
{
    elf_t *elf = extract_elf(filename);

    if (elf == NULL)
        return 1;
    if (!dump(elf))
        printf("nm: %s: no symbols\n", filename);
    return 0;
}