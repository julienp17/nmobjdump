/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu-20.04]
** File description:
** extract
*/

#include <stdlib.h>
#include "my_nm.h"

static elf_t *fill_elf(int fd, const size_t file_size, const char *filename);
static bool is_elf_file(const unsigned char ident[EI_NIDENT]);

elf_t *extract_elf(const char *filename)
{
    elf_t *elf = NULL;
    struct stat s;
    int fd = open(filename, O_RDONLY);

    if (fd == -1) {
        fprintf(stderr, "nm: '%s': No such file\n", filename);
        return NULL;
    }
    if (fstat(fd, &s) == -1) {
        perror("fstat: ");
        return NULL;
    }
    elf = fill_elf(fd, s.st_size, filename);
    if (close(fd) == -1)
        perror("close: ");
    return elf;
}

static elf_t *fill_elf(int fd, const size_t file_size, const char *filename)
{
    elf_t *elf = malloc(sizeof(elf_t));

    if (elf == NULL) {
        perror("malloc: ");
        return NULL;
    }
    elf->data = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (elf->data == MAP_FAILED) {
        perror("mmap: ");
        return NULL;
    }
    elf->ehdr = (Elf64_Ehdr *)elf->data;
    if (!is_elf_file(elf->ehdr->e_ident)) {
        fprintf(stderr, "nm: %s: file format not recognized\n", filename);
        return NULL;
    }
    elf->shdr = (Elf64_Shdr *)((unsigned char *)elf->data + elf->ehdr->e_shoff);
    elf->filename = strdup(filename);
    return elf;
}

static bool is_elf_file(const unsigned char ident[EI_NIDENT])
{
    return (memcmp(ident, ELFMAG, SELFMAG) == 0);
}