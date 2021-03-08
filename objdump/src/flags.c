/*
** EPITECH PROJECT, 2021
** objdump [WSL: Ubuntu-20.04]
** File description:
** flags
*/

#include "my_objdump.h"

uint32_t get_flags(const elf_t *elf)
{
    uint32_t flags = 0;
    const char *shname = NULL;
    bool has_symbols = false;

    flags |= elf->ehdr->e_type  == ET_EXEC ?    EXEC_P : 0;
    flags |= elf->ehdr->e_type  ==  ET_DYN ?   DYNAMIC : 0;
    flags |= elf->ehdr->e_type  ==  ET_REL ? HAS_RELOC : 0;
    flags |= elf->ehdr->e_phnum !=       0 ?   D_PAGED : 0;
    if (elf->strtable == NULL)
        return flags;
    for (size_t i = 0 ; i < elf->ehdr->e_shnum && !has_symbols ; i++) {
        shname = elf->strtable + elf->shdr[i].sh_name;
        if (strcmp(shname, ".dynsym") == 0 || strcmp(shname, ".symtab") == 0)
            has_symbols = true;
    }
    if (has_symbols)
        flags |= HAS_SYMS;
    return flags;
}

void dump_flags(const uint32_t flags)
{
    const flag_t flag_names[] = {
        {HAS_RELOC, "HAS_RELOC"},
        {EXEC_P, "EXEC_P"},
        {HAS_SYMS, "HAS_SYMS"},
        {DYNAMIC, "DYNAMIC"},
        {D_PAGED, "D_PAGED"},
        {0, "UNKNOWN"}
    };
    bool first_print = true;

    for (size_t i = 0 ; flag_names[i].flag != 0 ; i++) {
        if (flags & flag_names[i].flag) {
            if (first_print) {
                printf("%s", flag_names[i].name);
                first_print = false;
            } else {
                printf(", %s", flag_names[i].name);
            }
        }
    }
    printf("\n");
}