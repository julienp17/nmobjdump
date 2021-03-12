/*
** EPITECH PROJECT, 2021
** nmobjdump [WSL: Ubuntu-20.04]
** File description:
** symbol_type2
*/

#include "my_nm.h"

char get_text(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    return (
        shdr[sym->st_shndx].sh_type == SHT_PROGBITS
        && (shdr[sym->st_shndx].sh_flags == (SHF_EXECINSTR | SHF_ALLOC))
    ) ? 't' : 0;
}

char get_data(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    return (
        (shdr[sym->st_shndx].sh_type == SHT_PROGBITS
        && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        || shdr[sym->st_shndx].sh_type == SHT_DYNAMIC
    ) ? 'd' : 0;
}

char get_rodata(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    return (
        shdr[sym->st_shndx].sh_type == SHT_PROGBITS
        && shdr[sym->st_shndx].sh_flags == SHF_ALLOC
    ) ? 'r' : 0;
}

char get_init_array(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    return (
        (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT
        || ELF64_ST_TYPE(sym->st_info) == STT_NOTYPE)
        && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)
    ) ? 'd' : 0;
}