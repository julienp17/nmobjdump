/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu-20.04]
** File description:
** dump
*/

#include "my_nm.h"

static void dump_section_symbols(const elf_t *elf, size_t i);
static bool should_dump_symbol(const Elf64_Sym *symbol);
static void dump_symbol(const Elf64_Shdr *shdr,
                        const Elf64_Sym *symbol,
                        const uchar *strTbl);

bool dump(const elf_t *elf)
{
    bool dumped = false;

    for (size_t i = 0; i < elf->ehdr->e_shnum; i++) {
        if (elf->shdr[i].sh_type == SHT_SYMTAB) {
            dump_section_symbols(elf, i);
            dumped = true;
        }
    }
    return dumped;
}

static void dump_section_symbols(const elf_t *elf, size_t i)
{
    Elf64_Shdr *shdr = &(elf->shdr[i]);
    size_t size = shdr->sh_size / shdr->sh_entsize;
    uchar *strTbl = elf->data + elf->shdr[shdr->sh_link].sh_offset;
    Elf64_Sym *symbols = malloc(sizeof(Elf64_Sym) * size);

    memcpy(symbols, ((char *)elf->ehdr + shdr->sh_offset),
            sizeof(Elf64_Sym) * size);
    sort_symbols(symbols, size, strTbl);
    for (size_t i = 0 ; i < size ; i++)
        if (should_dump_symbol(&symbols[i]))
            dump_symbol(elf->shdr, &symbols[i], strTbl);
    free(symbols);
}

static bool should_dump_symbol(const Elf64_Sym *symbol)
{
    return (
        symbol->st_info != STT_FILE
        && symbol->st_name != 0
    );
}

static void dump_symbol(const Elf64_Shdr *shdr,
                        const Elf64_Sym *symbol,
                        const uchar *strTbl)
{
    char type = get_symbol_type(shdr, symbol);

    if (symbol->st_value == 0 && type != 'T')
        printf("%16c", ' ');
    else
        printf("%016x", (uint32_t)symbol->st_value);
    printf(" %c %s\n", type, &strTbl[symbol->st_name]);
}