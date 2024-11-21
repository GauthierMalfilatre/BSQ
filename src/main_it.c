/*
** EPITECH PROJECT, 2024
** BSQ_IT
** File description:
** Bsq but iteratif
*/
#include "../include/bsq.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

static char *create_map(char *size_c, char *pattern)
{
    int s = my_strlen(size_c) + 1;
    int size = my_getnbr(size_c);
    char *map = malloc((size + 1) * size + 1 + s);
    int pattern_len = my_strlen(pattern);
    int n_len = 0;
    int i = 0;

    my_strcpy(map, size_c);
    my_strcat(map, "\n");
    for (; i < (size + 1) * size; i++) {
        if ((i + 1) % (size + 1))
            map[i + s] = pattern[(i - n_len) % (pattern_len)];
        else {
            map[i + s] = '\n';
            ++n_len;
        }
    }
    map[i + s] = '\0';
    return map;
}

static int get_size(char *path)
{
    struct stat kronk_struct;

    if (lstat(path, &kronk_struct) == -1)
        return 0;
    return kronk_struct.st_size;
}

static int check_case(char *map, int *x, int value, int *exit)
{
    for (int i = 0; i < value + 1; i++) {
        if (map[(*x) + i] != '.' && map[(*x) + i] != '\n'
            && map[(*x) + i] != 'o') {
            (*exit) = 84;
            return 84;
        }
    }
    (*x) += value;
    return 0;
}

static int check_out(char *map, int x, int *ka, int opt)
{
    int i = 0;
    int j = 0;

    for (; 1; ++ka[5]) {
        for (i = 0; i < ka[5] + 1 && (x + i * (ka[0] + 1) + ka[5]) < (ka[0]
            + 1) * ka[1] && map[x + i * (ka[0] + 1) + ka[5]] == '.'; ++i);
        if (i != ka[5] + 1) {
            opt = 1;
            break;
        }
        for (j = 0; j < ka[5] + 1 && map[x + (ka[0] + 1) * ka[5] + j] == '.';
            ++j);
        if (j != ka[5] + 1)
            break;
    }
    if (ka[5] > ka[3]) {
        ka[2] = x;
        ka[3] = ka[5];
    }
    return (opt ? ka[5] : j);
}

static int fill_x(char *map, int *ka)
{
    for (int j = 0; j < ka[3]; j++) {
        for (int i = 0; i < ka[3]; i++) {
            map[ka[2] + j * (ka[0] + 1) + i] = 'x';
        }
    }
}

int bsq(char *map, int size)
{
    int st = 1;
    int ka[7] = {};

    for (; map[st - 1] >= '0' && map[st - 1] <= '9'; st++);
    ka[1] = my_getnbr(map);
    ka[0] ++;
    for (int i = 0; map[st + ka[0]] != '\n'; ka[0]++);
    if ((ka[0] + 1) * ka[1] + st != size || ka[6])
        return 84;
    for (int x = st; x < size; ++x) {
        if (map[x] != '.' && map[x] != '\n' && map[x] != 'o')
            return 84;
        if (x % (ka[0] + 1) + ka[5] < (ka[0] + 1) && map[x] == '.') {
            check_case(map, &x, check_out(map, x, ka, 0), &ka[6]);
            ka[5] = 0;
        }
    }
    fill_x(map, ka);
    return write(1, &map[st], size - st) && 0;
}

int main(int argc, char *const *argv)
{
    char *kronk_buffer;
    int fd;
    int size;
    int exitcode = 0;

    if (argc == 3) {
        kronk_buffer = create_map(argv[1], argv[2]);
        size = my_strlen(kronk_buffer);
    }
    if (argc == 2) {
        fd = open(argv[1], O_RDONLY);
        size = get_size(argv[1]);
        kronk_buffer = malloc(size);
        if (read(fd, kronk_buffer, size) == -1 || fd == -1)
            return 84 + 0 * write(2, "Error while loading file\n", 26);
    } else if (argc != 2 && argc != 3)
        return 84;
    exitcode = bsq(kronk_buffer, size);
    free(kronk_buffer);
    return close(fd) * 0 + exitcode;
}
