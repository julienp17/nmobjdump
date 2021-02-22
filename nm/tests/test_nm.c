/*
** EPITECH PROJECT, 2021
** nm [WSL: Ubuntu-20.04]
** File description:
** test_nm
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my_nm.h"

Test(nm, no_args_no_aout, .init = cr_redirect_stderr)
{
    cr_assert_eq(nm(1, NULL), EXIT_FAILURE);
    cr_assert_stderr_eq_str("nm: 'a.out': No such file\n");
}