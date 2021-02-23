/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu-20.04]
** File description:
** objdump
*/

#include "my_objdump.h"

int objdump_main(int ac, char **av)
{
    if (ac == 1) {
        if (FILE_EXISTS("./a.out"))
            return objdump_file("./a.out");
        print_help();
        return MY_EXIT_FAILURE;
    }
    for (size_t i = 1 ; av[i] ; i++)
        objdump_file(av[i]);
    return 0;
}

int objdump_file(const char *filename)
{
    int exit_code = 0;
    int fd = open(filename, O_RDONLY);

    if (fd == -1) {
        print_help();
        return MY_EXIT_FAILURE;
    }
    if (!is_elf_file(fd))
        return MY_EXIT_FAILURE;
    printf("\n%s:\tfile format elf64-x86-64", filename);
    exit_code = objdump(fd);
    if (close(fd) == -1) {
        perror("close: ");
        return MY_EXIT_FAILURE;
    }
    return exit_code;
}

int objdump_fd(int fd)
{
    Elf64_Ehdr *elf = NULL;
    struct stat s;
    int exit_code = 0;

    if (fstat(fd, &s) == -1) {
        perror("fstat: ");
        return MY_EXIT_FAILURE;
    }
    elf = (Elf64_Ehdr *) mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (elf == MAP_FAILED) {
        perror("fstat: ");
        return MY_EXIT_FAILURE;
    }
    exit_code = objdump_elf(elf);
    if (munmap((void *)elf, s.st_size) == -1) {
        perror("munmap: ");
        return MY_EXIT_FAILURE;
    }
    return exit_code;
}

int objdump_elf(Elf64_Ehdr *elf)
{
    printf("architecture: ");
    printf("mmap : %p\n", elf);
    printf("Section  Header  Table : addr = %08lx, nb = %d\n",elf ->e_shoff , elf ->e_shnum);
    return 0;
}

void print_help(void)
{
    printf("Usage: objdump <options(s)> <file(s)>\n"
            " Display information from object <file(s)>.\n");
}

bool is_elf_file(int fd)
{
    char const buf[SELFMAG] = "";
    ssize_t bytes = read(fd, buf, SELFMAG);

    return (bytes == 4 && strcmp(buf, ELFMAG));
}