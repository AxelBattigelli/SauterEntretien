#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int is_delim(char character, char *delim)
{
    for (int i = 0; delim[i] != '\0'; i++) {
        if (character == delim[i])
            return 1;
    }
    return 0;
}

int nbr_words(char *arg, char *delim)
{
    int len = 0;
    int prev_space = 1;

    if (arg == NULL || strlen(arg) == 0)
        return 0;
    for (int i = 0; arg[i] != '\0'; i++) {
        if (is_delim(arg[i], delim) == 0 && prev_space == 1) {
            len += 1;
            prev_space = 0;
        }
        if (is_delim(arg[i], delim) == 1)
            prev_space = 1;
    }
    return len;
}

char *add_word(char *str, int *i, char *delim)
{
    char *word;
    int len = 0;
    int j;

    for (len = 0; is_delim(str[*i +len], delim) == 0; len ++) {
        if (str[*i + len] == '\0')
            break;
    }
    word = malloc(sizeof(char) * (len + 1));
    for (j = 0; j < len; j++) {
        word[j] = str[*i];
        *i += 1;
    }
    *i -= 1;
    word[j] = '\0';
    return word;
}

char **my_str_to_word_array(char *str, char *delim)
{
    int len = nbr_words(str, delim);
    char **word_array;
    int line = 0;
    int i;

    if (len == 0)
        return NULL;
    word_array = malloc(sizeof(char *) * (len + 1));
    for (i = 0; str[i] != '\0'; i++) {
        if (is_delim(str[i], delim) == 0) {
            word_array[line] = add_word(str, &i, delim);
            line += 1;
        }
    }
    word_array[line] = NULL;
    return word_array;
}
