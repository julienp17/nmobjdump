/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu-20.04]
** File description:
** dump
*/

#include "my_objdump.h"

static void dump_section(const elf_t *elf, size_t i);
static bool should_print_section(const Elf64_Shdr *shdr);
static void print_ascii(const unsigned char *content, size_t j, size_t size);

void dump(const elf_t *elf)
{
    uint32_t flags = get_flags(elf);

    printf ("\n%s:     file format elf64-x86-64\n"
            "architecture: i386:x86-64, flags 0x%08x:\n",
            elf->filename, flags);
    dump_flags(flags);
    printf("start address 0x%016lx\n\n", elf->ehdr->e_entry);
    for (size_t i = 0; i < elf->ehdr->e_shnum; i++)
        dump_section(elf, i);
}

static void dump_section(const elf_t *elf, size_t i)
{
    char *sec_name = (char *)(elf->strtable + elf->shdr[i].sh_name);
    unsigned char *content =
        (unsigned char *)((char *)elf->ehdr + elf->shdr[i].sh_offset);

    if (!should_print_section(&(elf->shdr[i])))
        return;
    printf("Contents of section %s:", sec_name);
    for (size_t j = 0 ; j < elf->shdr[i].sh_size ; j++) {
        if (j % 16 == 0)
            printf("\n %04lx ", j);
        printf("%02x", content[j]);
        if ((j + 1) % 4 == 0)
            printf(" ");
        if ((j + 1) % 16 == 0 || j + 1 == elf->shdr[i].sh_size)
            print_ascii(content, j, elf->shdr[i].sh_size);
    }
    printf("\n");
}

static void print_ascii(const unsigned char *content, size_t j, size_t size)
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

static bool should_print_section(const Elf64_Shdr *shdr)
{
    return (
        shdr->sh_size > 0
        && shdr->sh_type != SHT_NOBITS
        && shdr->sh_type != SHT_SYMTAB
        && shdr->sh_type != SHT_RELA
        && shdr->sh_type != SHT_REL
        && shdr->sh_type != SHT_STRTAB
    );
}