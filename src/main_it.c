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

static int get_size(char *path)
{
    struct stat kronk_struct;

    if (lstat(path, &kronk_struct) == -1)
        return 0;
    return kronk_struct.st_size;
}

static int check_out(char *map, int x, int *kronk_array)
{
    int i = 0;
    int j = 0;

    while (1) {
        i = 0;
        j = 0;
        for (; i < kronk_array[5] + 1 && (x + i * (kronk_array[0] + 1) + kronk_array[5]) < (kronk_array[0] + 1) * kronk_array[1] && map[x + i * (kronk_array[0] + 1) + kronk_array[5]] == '.'; ++i);
        if (i != kronk_array[5] + 1) {
            break; 
        }
        for (; j < kronk_array[5] + 1 && map[x + (kronk_array[0] + 1) * kronk_array[5] + j] == '.'; ++j);
        if (j != kronk_array[5] + 1) {
            break;
        }
        ++kronk_array[5];
    }
    if (kronk_array[5] > kronk_array[3]) {
        kronk_array[2] = x;
        kronk_array[3] = kronk_array[5];
    }
    return 0; //(kronk_array[5] > 1) ? kronk_array[5] - 1 : 0;
}

static int bsq(char *map, int size)
{
    int st = 1;
    int kronk_array[6] = {};

    /* Get length and width */
    for (; map[st - 1] >= '0' && map[st - 1] <= '9'; st++);
    kronk_array[1] = my_getnbr(map);
    for (int i = 0; map[st + kronk_array[0]] != '\n'; kronk_array[0]++);

    /* Find BSQ */    
    for (int x = st; map[x]; ++x) {
        if ( map[x] == '.') {// x % (kronk_array[0] + 1) + kronk_array[5] < (kronk_array[0] + 1) && map[x] == '.') {
            check_out(map, x, kronk_array);
            kronk_array[5] = 0;
        }
    }
    //printf("RES : %i : %i\n", kronk_array[2], kronk_array[3]);
    /* Fill biggest square with 'x' */
    for (int j = 0; j < kronk_array[3]; j++) {
        for (int i = 0; i < kronk_array[3]; i++) {
            map[kronk_array[2] + j * (kronk_array[0] + 1) + i] = 'x';
        }
    }
    //map[9610] = 'Q';
    write(1, &map[st], size - st);

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
    kronk_buffer = malloc(size);
    if (read(fd, kronk_buffer, size) == -1) {
        return 84 + 0 * write(2, "Error while loading file\n", 26);
    }
    bsq(kronk_buffer, size);
    free(kronk_buffer);
    close(fd);
    return 0;
}
