/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu-20.04]
** File description:
** dump
*/

#include "my_objdump.h"

void dump(const elf_t *elf)
{
    uint32_t flags = get_flags(elf);

    printf ("\n%s:     file format elf64-x86-64\n"
            "architecture: i386:x86-64, flags 0x%08x:\n",
            elf->filename, flags);
    dump_flags(flags);
    printf("start_address 0x%016lx\n\n", elf->ehdr->e_entry);
    // for (size_t i = 0 ; i < elf->ehdr->e_shnum ; i++)
    //     dump_section_contents(elf, i);
}