/*
** EPITECH PROJECT, 2024
** MY_STRCPY
** File description:
** Copy a string into another
*/
#include "../../include/bsq.h"

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    for (; i < my_strlen(src); i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}

char *my_strcat(char *dest, char const *src)
{
    int length = my_strlen(dest);
    int i = 0;

    for (; src[i] != '\0'; i++) {
        dest[length + i] = src[i];
    }
    dest[length + i + 1] = '\0';
    return dest;
}

int my_strlen(char const *str)
{
    int i = 0;

    for (; str[i]; i++);
    return i;
}

int my_nbrlen(int n)
{
    int res = 0;

    for (; n > 0;) {
        ++res;
        n /= 10;
    }
    return res;
}
