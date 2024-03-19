#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "../include/header.h"


static char *my_strupcase(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if ('A' <= str[i] && str[i] <= 'Z')
            str[i] += 32;
        i++;
    }
    return str;
}

static int add(data_t **tmp, char *word)
{
    data_t *elem = malloc(sizeof(data_t));

    elem->next = *tmp;
    elem->word = strdup(word);
    elem->count = 1;
    *tmp = elem;

    return 0;
}

static int compare(char *word, data_t **list)
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

static void find_occurences(data_t *list, char *keyword)
{
    data_t *tmp;

    tmp = list;
    while (tmp != NULL) {
        if (strcmp(keyword, tmp->word) == 0) {
            printf("\"varieties\" appear : %d times\n", tmp->count);
            break;
        }
        tmp = tmp->next;
    }
}

static void find_25th_word(data_t *list)
{
    data_t *tmp;
    char *word = "";
    int i = 0;

    tmp = list;
    while (tmp->next != NULL) {
        if (tmp->count > tmp->next->count) {
            int elem = tmp->count;
            tmp->count = tmp->next->count;
            tmp->next->count = elem;
        }
        tmp = tmp->next;
    }
    tmp = list;
    for (int i = 0; i < 25; i++)
        word = tmp->word;  
    printf("The 25th most used word is : %s \n", word);
}

static void free_all(char *buff, data_t *list, char **array)
{
    data_t *tmp = list;;
    data_t *tmp2;

    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
    while (tmp != NULL) {
        free(tmp->word);
        tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2);
    }
    free(buff);
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
    find_occurences(list, "varieties");
    find_25th_word(list);
    free_all(buff, list, array);
    return 0;
}
