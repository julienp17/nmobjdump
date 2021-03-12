/*
** EPITECH PROJECT, 2021
** nmobjdump [WSL: Ubuntu-20.04]
** File description:
** symbol_type1
*/

#include "my_nm.h"

char get_absolute(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    (void)shdr;
    return sym->st_shndx == SHN_ABS ? 'a' : 0;
}

char get_common(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    (void)shdr;
    return sym->st_shndx == SHN_COMMON ? 'c' : 0;
}

char get_undefined(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    (void)shdr;
    return sym->st_shndx == SHN_UNDEF ? 'u' : 0;
}

char get_weak(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    (void)shdr;
    if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
        if (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
            return 'v';
        return 'w';
    }
    return 0;
}

char get_bss(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    return shdr[sym->st_shndx].sh_type == SHT_NOBITS ? 'b' : 0;
}