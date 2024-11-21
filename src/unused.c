/*
** EPITECH PROJECT, 2024
** Sugar david
** File description:
** AHA
*/
#include "../include/bsq.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

static int get_size(char *path)
{
    struct stat kronk_struct;

    if (lstat(path, &kronk_struct) == -1)
        return 0;
    return kronk_struct.st_size;
}

static int check_out(char *map, int x, int *k_a, int quit)
{
    int i = 0;
    int j = 0;

    if (quit || x % k_a[0] + k_a[5] > k_a[0] || x % k_a[1] + k_a[5] > k_a[1]
        || map[x] != '.') {
        k_a[2] = (k_a[5] > k_a[3]) ? x : k_a[2];
        k_a[3] = k_a[5] > k_a[3] ? k_a[5] : k_a[3];
        return 0;
    }
    for (; i < k_a[5] + 1; i++) {
        if (map[x + i * (k_a[0] + 1) + k_a[5]] != '.')
            return check_out(map, x, k_a, 1);
    }
    for (; j < k_a[5] + 1; j++) {
        if (map[x + (k_a[0] + 1) * k_a[5] + j] != '.')
            return check_out(map, x, k_a, 1);
    }
    ++k_a[5];
    return check_out(map, x, k_a, 0);
}

static int bsq(char *map, int size)
{
    int st = 1;
    int k_a[6] = {};
    int x = st;

    for (; map[st - 1] >= '0' && map[st - 1] <= '9'; st++);
    k_a[1] = my_getnbr(map);
    for (int i = 0; map[st + k_a[0]] != '\n'; k_a[0]++);
    for (; map[x]; x++) {
        check_out(map, x, k_a, 0);
        x += k_a[5] + 1;
        k_a[5] = 0;
    }
    for (int j = 0; j < k_a[3]; j++) {
        for (int i = 0; i < k_a[3]; i++) {
            map[k_a[2] + j * (k_a[0] + 1) + i] = 'x';
        }
    }
    write(1, &map[st], size);
    return 0;
}

int main(int argc, char *const *argv)
{
    char *kronk_buffer;
    int fd = open(argv[1], O_RDONLY);
    int size = get_size(argv[1]);

    if (argc != 2 || fd == -1 || !size) {
        return 84 + 0 * write(2, "You must handle a file fckin retard\n", 37);
    }
    kronk_buffer = malloc(size + 1);
    if (read(fd, kronk_buffer, size) == -1) {
        return 84 + 0 * write(2, "Error while loading file\n", 26);
    }
    bsq(kronk_buffer, size);
    free(kronk_buffer);
    close(fd);
    return 0;
}
