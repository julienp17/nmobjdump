/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu-20.04]
** File description:
** symbol_type
*/

#include "my_nm.h"

static char get_weak(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    (void)shdr;
    if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
        if (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
            return 'v';
        return 'w';
    }
    return 0;
}

static char get_absolute(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    (void)shdr;
    return sym->st_shndx == SHN_ABS ? 'a' : 0;
}

static char get_common(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    (void)shdr;
    return sym->st_shndx == SHN_COMMON ? 'c' : 0;
}

static char get_undefined(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    (void)shdr;
    return sym->st_shndx == SHN_UNDEF ? 'u' : 0;
}

static char get_bss(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    return shdr[sym->st_shndx].sh_type == SHT_NOBITS ? 'b' : 0;
}

static char get_text(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    return (
        shdr[sym->st_shndx].sh_type == SHT_PROGBITS
        && (shdr[sym->st_shndx].sh_flags == (SHF_EXECINSTR | SHF_ALLOC))
    ) ? 't' : 0;
}

static char get_data(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    return (
        (shdr[sym->st_shndx].sh_type == SHT_PROGBITS
        && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        || shdr[sym->st_shndx].sh_type == SHT_DYNAMIC
    ) ? 'd' : 0;
}

static char get_rodata(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    return (
        shdr[sym->st_shndx].sh_type == SHT_PROGBITS
        && shdr[sym->st_shndx].sh_flags == SHF_ALLOC
    ) ? 'r' : 0;
}

static char get_init_array(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    return (
        (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT
        || ELF64_ST_TYPE(sym->st_info) == STT_NOTYPE)
        && shdr[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)
    ) ? 'd' : 0;
}

char get_symbol_type(const Elf64_Shdr *shdr, const Elf64_Sym *sym) {
    char type = 0;
    char (*type_getters[])(const Elf64_Shdr *, const Elf64_Sym *) = {
        &get_weak, &get_absolute, &get_common, &get_undefined, &get_bss,
        &get_data, &get_rodata, &get_init_array, &get_text, NULL
    };
    char (*get_type)(const Elf64_Shdr *, const Elf64_Sym *) = NULL;

    for (size_t i = 0 ; type == 0 && type_getters[i] != NULL ; i++) {
        get_type = type_getters[i];
        type = get_type(shdr, sym);
    }
    if (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL)
        type = toupper(type);
    return type != 0 ? type : '?';
}