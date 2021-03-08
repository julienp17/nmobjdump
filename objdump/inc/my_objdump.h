/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu-20.04]
** File description:
** my_objdump
*/

#ifndef INC_MY_OBJDUMP_H_
#define INC_MY_OBJDUMP_H_

#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MY_EXIT_FAILURE         2
#define FILE_EXISTS(fname)      ((access(fname, F_OK)) == (0))

#define HAS_RELOC               ((unsigned int)(0b000000001))
#define EXEC_P                  ((unsigned int)(0b000000010))
#define HAS_SYMS                ((unsigned int)(0b000010000))
#define DYNAMIC                 ((unsigned int)(0b001000000))
#define D_PAGED                 ((unsigned int)(0b100000000))

typedef struct elf {
    char *filename;
    void *data;
    void *strtable;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
} elf_t;

elf_t *extract_elf(const char *filename);

typedef struct flag {
    unsigned int flag;
    char *name;
} flag_t;

uint32_t get_flags(const elf_t *elf);
void dump_flags(const uint32_t flags);

int objdump(const char *filename);
void dump(const elf_t *elf);
void print_help(void);

#endif  // INC_MY_OBJDUMP_H_
