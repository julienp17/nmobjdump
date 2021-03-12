/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu-20.04]
** File description:
** dump
*/

#include "my_objdump.h"

static void dump_section(const elf_t *elf, size_t i);
static void print_ascii(const unsigned char *content, size_t j, size_t size);
static bool should_print_section(const Elf64_Shdr *shdr,
                                const char *sec_name,
                                const Elf64_Half type);

void dump(const elf_t *elf)
{
    printf ("\n%s:     file format elf64-x86-64\n"
            "architecture: i386:x86-64, flags 0x%08x:\n",
            elf->filename, elf->flags);
    dump_flags(elf->flags);
    printf("start address 0x%016lx\n\n", elf->ehdr->e_entry);
    for (size_t i = 0; i < elf->ehdr->e_shnum; i++)
        dump_section(elf, i);
}

static void dump_section(const elf_t *elf, size_t i)
{
    Elf64_Shdr *shdr = &(elf->shdr[i]);
    char *sec_name = (char *)(elf->strtable + shdr->sh_name);
    uchar *content = (uchar *)((char *)elf->ehdr + shdr->sh_offset);

    if (!should_print_section(shdr, sec_name, elf->ehdr->e_type))
        return;
    printf("Contents of section %s:", sec_name);
    for (size_t j = 0 ; j < shdr->sh_size ; j++) {
        if (j % 16 == 0)
            printf("\n %04x ", (uint32_t)(shdr->sh_addr + j));
        printf("%02x", content[j]);
        if ((j + 1) % 4 == 0)
            printf(" ");
        if ((j + 1) % 16 == 0 || j + 1 == shdr->sh_size)
            print_ascii(content, j, shdr->sh_size);
    }
    printf("\n");
}

static void print_ascii(const uchar *content, size_t j, size_t size)
{
    size_t start = 16 * (j / 16);

    for (size_t k = j + 1 ; k % 16 != 0 ; k++) {
        printf("  ");
        if ((k + 1) % 4 == 0)
            printf(" ");
    }
    printf(" ");
    for (size_t k = start ; k < start + 16 ; k++) {
        if (k >= size)
            printf(" ");
        else if (isprint(content[k]))
            printf("%c", content[k]);
        else
            printf(".");
    }
}

static bool should_print_section(const Elf64_Shdr *shdr,
                                const char *sec_name,
                                const Elf64_Half type)
{
    if (shdr->sh_type == SHT_RELA || shdr->sh_type == SHT_REL)
        return type == ET_EXEC || type == ET_DYN;
    return (
        shdr->sh_size > 0
        && shdr->sh_type != SHT_NOBITS
        && shdr->sh_type != SHT_SYMTAB
        && strcmp(sec_name, ".strtab") != 0
        && strcmp(sec_name, ".shstrtab") != 0
    );
}