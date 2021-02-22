/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu-20.04]
** File description:
** nm
*/

#include <stdio.h>
#include <stdlib.h>

int nm(int ac, char **av)
{
    if (ac == 1) {
        fprintf(stderr, "nm: '%s': No such file\n", "a.out");
        return EXIT_FAILURE;
    }
    (void)av;
    return EXIT_SUCCESS;
}