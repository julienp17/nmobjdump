/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu-20.04]
** File description:
** dump
*/

#include "my_objdump.h"

static void dump_section(const elf_t *elf, size_t i);
static bool should_print_section(const Elf64_Shdr *shdr);

void dump(const elf_t *elf)
{
    uint32_t flags = get_flags(elf);

    printf ("\n%s:     file format elf64-x86-64\n"
            "architecture: i386:x86-64, flags 0x%08x:\n",
            elf->filename, flags);
    dump_flags(flags);
    printf("start_address 0x%016lx\n\n", elf->ehdr->e_entry);
    for (size_t i = 0; i < elf->ehdr->e_shnum; i++) {
        dump_section(elf, i);
    }
    // for (size_t i = 0 ; i < elf->ehdr->e_shnum ; i++) {}
    //     dump_section_contents(elf, i);
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
        if (j != 0 && j + 1 % 4 == 0 && j + 1 % 16 != 0)
            printf(" ");
    }
    printf("\n");
}

static bool should_print_section(const Elf64_Shdr *shdr)
{
    return (
        shdr->sh_size > 0
        && shdr->sh_type != SHT_NOBITS
        && shdr->sh_type != SHT_SYMTAB
    );
}