/*
** EPITECH PROJECT, 2024
** Sugar david
** File description:
** AHA
*/
#include <unistd.h>
#include "../../include/bsq.h"

static int check_overflow(char const *i, int nbr, int neg)
{
    if (neg && nbr >= 214748364 && *i - 48 > 2147483647 - (nbr) * 10) {
        return 1;
    } else if (!neg && nbr <= -214748364 && *i - 48 < -2147483648 + nbr * 10) {
        return 1;
    }
    return 0;
}

static int check_digit(char const *i)
{
    return (*i >= '0' && *i <= '9');
}

static int check_neg(char const *i, int nbr, int neg)
{
    if (*i == '-' && !nbr) {
        return -1;
    }
    return 1;
}

static int check(char const *i, int nbr, int neg)
{
    int temp_nbr = nbr;

    if (check_digit(i)) {
        if (neg == -1 && nbr > 0) {
            temp_nbr *= -1;
        }
        return temp_nbr * 10 + neg * (*i - 48);
    }
    return temp_nbr;
}

int my_getnbr(char const *str)
{
    int nbr = 0;
    int neg = 1;

    for (char const *i = str; *i != '\0'; i++) {
        if (check_overflow(i, nbr, neg)) {
            return 0;
        }
        if (check_digit(i) || *i == '-' || *i == '+') {
            neg *= check_neg(i, nbr, neg);
            nbr = check(i, nbr, neg);
        } else {
            return nbr;
        }
    }
    return nbr;
}
