/*
** EPITECH PROJECT, 2021
** objdump
** File description:
** Main
*/

#include "my_objdump.h"

int main(int ac, char **av)
{
    int status = 0;
    int tmp = 0;

    if (ac == 1)
        return objdump("a.out");
    for (size_t i = 1 ; av[i] ; i++) {
        tmp = objdump(av[i]);
        if (tmp != 0)
            status = tmp;
        fflush(stdout);
        fflush(stderr);
    }
    return status;
}