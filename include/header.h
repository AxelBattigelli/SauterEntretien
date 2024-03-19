#ifndef MY_
    #define MY_

typedef struct data_s {
    char *word;
    int count;
    struct data_s *next;
} data_t;

char **my_str_to_word_array(char *str, char *delim);

#endif
