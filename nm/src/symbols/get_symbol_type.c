/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu-20.04]
** File description:
** symbol_type
*/

#include "my_nm.h"

char get_symbol_type(const Elf64_Shdr *shdr, const Elf64_Sym *sym)
{
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