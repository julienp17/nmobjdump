/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu-20.04]
** File description:
** sort
*/

#include "my_nm.h"

static int sym_cmp(const char *s1, const char *s2);

void sort_symbols(Elf64_Sym *symbols, const size_t size, const uchar *strTbl) {
    Elf64_Sym tmp;
    char *name1 = NULL;
    char *name2 = NULL;

    for (size_t i = 0 ; i < size - 1 ; i++) {
        for (size_t j = 0 ; j < size - i - 1 ; j++) {
            name1 = (char *)&strTbl[symbols[j].st_name];
            name2 = (char *)&strTbl[symbols[j + 1].st_name];
            if (sym_cmp(name1, name2) > 0) {
                tmp = symbols[j];
                symbols[j] = symbols[j + 1];
                symbols[j + 1] = tmp;
            }
        }
    }
}

static int sym_cmp(const char *s1, const char *s2) {
    int ret = 0;
    bool fst_unclean = false;
    bool snd_unclean = false;

    while (s1[0] == '_' || s1[0] == '@') {
        s1++;
        fst_unclean = true;
    }
    while (s2[0] == '_' || s2[0] == '@') {
        s2++;
        snd_unclean = true;
    }
    ret = strcasecmp(s1, s2);
    if (ret == 0 && (fst_unclean || snd_unclean)) {
        if (fst_unclean)
            return -1;
        else
            return 1;
    }
    return ret;
}