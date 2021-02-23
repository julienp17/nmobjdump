/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu-20.04]
** File description:
** my_objdump
*/

#ifndef MY_OBJDUMP_H_
#define MY_OBJDUMP_H_

#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#define MY_EXIT_FAILURE     2

#define FILE_EXISTS(fname) ((access(fname, F_OK)) == (0))

int objdump_main(int ac, char **av);
int objdump_file(const char *filename);
int objdump_fd(int fd);
int objdump_elf(Elf64_Ehdr *elf);

bool is_elf_file(int fd);
void print_help(void);

#endif /* !MY_OBJDUMP_H_ */
