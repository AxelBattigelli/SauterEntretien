#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "../include/header.h"


char *my_strupcase(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if ('A' <= str[i] && str[i] <= 'Z')
            str[i] += 32;
        i++;
    }
    return str;
}

int add(data_t **tmp, char *word)
{
    data_t *elem = malloc(sizeof(data_t));

    elem->next = *tmp;
    elem->word = strdup(word);
    elem->count = 1;
    *tmp = elem;

    return 0;
}

int compare(char *word, data_t **list)
{
    data_t *tmp = *list;

    while (tmp != NULL) {        
        if (strcmp(word, tmp->word) == 0) {
            tmp->count += 1;
            return 1;
        }
        tmp = tmp->next;
    }
    add(list, word);
}

int main(int ac, char **av)
{
    char **array;
    char *buff;
    int cnt;
    int fd;
    struct stat stats;
    data_t *list = NULL;
    data_t *tmp;

    if (ac != 2) {
        printf("USAGE:\n\t./prog [file]\n");
        return 84;
    }
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        return 84;
    stat(av[1], &stats);
    buff = malloc(sizeof(char) * (stats.st_size + 1));
    cnt = read(fd, buff, stats.st_size);
    buff[cnt] = '\0';
    buff = my_strupcase(buff);
    array = my_str_to_word_array(buff, " ");
    for (int i = 0; array[i] != NULL; i++)
        compare(array[i], &list);
    tmp = list;
    while (tmp != NULL) {
        if (strcmp("varieties", tmp->word) == 0)   
            printf("\"varieties\" appear : %d times\n", tmp->count);
        tmp = tmp->next;
    }    
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
    free(list);
    free(tmp);
    free(buff);
    return 0;
}
