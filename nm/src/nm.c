/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu-20.04]
** File description:
** nm
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <elf.h>
#include <unistd.h>
#include "my_nm.h"

int nm(int ac, char **av)
{
    if (ac == 1)
    {
        fprintf(stderr, "nm: '%s': No such file\n", "a.out");
        return EXIT_FAILURE;
    }
    nm_file(av[1]);
    (void)av;
    return EXIT_SUCCESS;
}

int nm_file(const char *filename)
{
    int fd;
    void *buf;
    struct stat s;
    // Elf64_Ehdr *elf;
    fd = open(filename, O_RDONLY);
    if (fd != -1)
    {
        fstat(fd, &s);
        buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        if (buf != NULL)
        {
            printf("mmap(%s) : %p\n%s\n", filename, buf, (char *)buf);
            munmap(buf , s.st_size);
            // printf("mmap(%s) : %8p\n", filename, buf);
            // elf = buf;
            // printf("Section  Header  Table : addr = %8ld, nb = %d\n", elf->e_shoff , elf ->e_shnum);
        }
        else
        {
            perror("mmap");
        }
        close(fd);
    }
    return EXIT_SUCCESS;
}