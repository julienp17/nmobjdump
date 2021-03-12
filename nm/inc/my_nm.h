/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu-20.04]
** File description:
** my_nm
*/

#ifndef INC_MY_NM_H_
#define INC_MY_NM_H_

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
#include <stdlib.h>

#define MY_EXIT_FAILURE         2
#define FILE_EXISTS(fname)      ((access(fname, F_OK)) == (0))

#define HAS_RELOC               ((unsigned int)(0b000000001))
#define EXEC_P                  ((unsigned int)(0b000000010))
#define HAS_SYMS                ((unsigned int)(0b000010000))
#define DYNAMIC                 ((unsigned int)(0b001000000))
#define D_PAGED                 ((unsigned int)(0b100000000))

typedef unsigned char uchar;
typedef struct elf {
    char *filename;
    void *data;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
} elf_t;

elf_t *extract_elf(const char *filename);

int nm(const char *filename);
bool dump(const elf_t *elf);
void sort_symbols(Elf64_Sym *symbols, const size_t size, const uchar *strTbl);


char get_symbol_type(const Elf64_Shdr *shdr, const Elf64_Sym *sym);
char get_absolute(const Elf64_Shdr *shdr, const Elf64_Sym *sym);
char get_common(const Elf64_Shdr *shdr, const Elf64_Sym *sym);
char get_undefined(const Elf64_Shdr *shdr, const Elf64_Sym *sym);
char get_bss(const Elf64_Shdr *shdr, const Elf64_Sym *sym);
char get_text(const Elf64_Shdr *shdr, const Elf64_Sym *sym);
char get_data(const Elf64_Shdr *shdr, const Elf64_Sym *sym);
char get_rodata(const Elf64_Shdr *shdr, const Elf64_Sym *sym);
char get_init_array(const Elf64_Shdr *shdr, const Elf64_Sym *sym);
char get_weak(const Elf64_Shdr *shdr, const Elf64_Sym *sym);


#endif  // INC_MY_NM_H_
