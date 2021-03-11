/*
** EPITECH PROJECT, 2021
** nm
** File description:
** Main
*/

#include "my_nm.h"

int main(int ac, char **av)
{
    int status = 0;
    int tmp = 0;

    if (ac == 1)
        return nm("a.out");
    else if (ac == 2)
        return nm(av[1]);
    for (size_t i = 1 ; av[i] ; i++) {
        printf("\n%s:\n", av[i]);
        tmp = nm(av[i]);
        if (tmp != 0)
            status = tmp;
    }
    return status;
}