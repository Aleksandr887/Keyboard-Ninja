#include "func.h"
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int begin(char* str[])
{
    printf("%s\n", str[0]);
    getchar();
    __fpurge(stdin);
    int tik = 0;
    printf("%s\n", str[1]);
    while (1) {
        if (tik < 3) {
            printf("%d...\n", 3 - tik);
        } else {
            printf("%s\n", str[12]);
            break;
        }
        sleep(1);
        tik++;
    }
    sleep(1);
    system("clear");
    return 0;
}

void give_name_playlist(char name[], size_t max_name)
{
    printf("Write the name of your playlist.\nIf the playlist already exists, "
           "write its name\n");
    scanf("%s", name);
    strcat(name, ".txt");
    if (strlen(name) > max_name) {
        printf("Playlist title too long\n");
        exit(0);
    }
    check_playlist(name, max_name);
}

void check_playlist(char name[], size_t max_name)
{
    if ((strncmp(name, "eng.txt", 7) == 0)
        || (strncmp(name, "rus.txt", 7) == 0)) {
        system("clear");
        printf("Cannot edit standart playlists\n");
        give_name_playlist(name, max_name);
    }
}

void give_words_playlist(FILE*** f)
{
    size_t max_name = 30;
    char name_playlist[max_name];
    give_name_playlist(name_playlist, max_name);
    char words[80];
    **f = fopen(name_playlist, "a");
    while (1) {
        system("clear");
        printf("Enter the words for your playlist.\nWhen done, write the "
               "\"end\".\nIf you want to clear the entire playlist, write "
               "\"delall\"\n");
        printf("Write word: ");
        scanf("%s", words);
        if (strcmp("end", words) == 0) {
            fclose(**f);
            **f = fopen(name_playlist, "r");
            if (getc(**f) == EOF) {
                printf("File is empty!\n");
                exit(0);
            }
            break;
        }
        if (strcmp("delall", words) == 0) {
            delete_all_playlist(&f, name_playlist);
            continue;
        }
        fputs(words, **f);
        fputs("\n", **f);
    }
}

void delete_all_playlist(FILE**** f, char name_playlist[])
{
    fclose(***f);
    ***f = fopen(name_playlist, "w");
    fclose(***f);
    ***f = fopen(name_playlist, "a");
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void print(int correct, int uncorrect, double time, char* str[])
{
    system("clear");
    printf("%s %d\n%s %d\n%s %lf\n",
           str[4],
           correct,
           str[5],
           uncorrect,
           str[6],
           time);
    while (1) {
        char sett[40];
        printf("\n%s\n", str[9]);
        scanf("%s", sett);
        if (strcmp(sett, str[8]) == 0) {
            main();
            break;
        } else if (strcmp(sett, str[10]) == 0) {
            exit(0);
        } else {
            printf("%s\n", str[11]);
        }
    }
}

void max_len_amount_lines(int* amount, int* maxlen, FILE* f)
{
    char ch;
    int i = 0;
    while (1) {
        ch = fgetc(f);
        if ((ch == '\n') || (ch == EOF)) {
            if (*maxlen < i)
                *maxlen = i;
            i = 0;
            if (ch == EOF)
                break;
            ++*amount;
        } else
            i++;
    }
    fseek(f, 0, SEEK_SET);
}

int getrand(int min, int max)
{
    srand(time(NULL));
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int set_lang(char lang[], FILE** f, char* str[], int maxlen, int amount)
{
    int result;
    while (1) {
        if (strcmp(lang, "rus") == 0) {
            *f = fopen("rus.txt", "r");
            result = 1;
            break;
        } else if (strcmp(lang, "eng") == 0) {
            *f = fopen("eng.txt", "r");
            result = 2;
            break;
        } else if (strcmp(lang, "other") == 0) {
            strcpy(lang, "eng");
            give_words_playlist(&f);
            break;
        } else {
            system("clear");
            printf("Don't understand what that means\n");
            printf("Choose language\neng\nrus\nother\n");
            scanf("%s", lang);
        }
    }
    return result;
}

void language(char lang[], char* str[], int maxlen, int amount)
{
    char lan[4];

    FILE* conf = fopen("lang.cfg", "r");

    maxlen += 2;
    while (strcmp(lan, lang) != 0) {
        fgets(lan, 4, conf);
    }
    char* buf = malloc(maxlen * sizeof(char));
    fgets(buf, maxlen, conf);
    for (int i = 0; i < (amount - 2) / 2; i++) {
        str[i] = malloc(maxlen * sizeof(char));
        fgets(str[i], maxlen, conf);
    }
    fclose(conf);
    free(buf);
}

int rm_last_sym(char* str[], int amount)
{
    for (int i = 0; i < (amount - 2) / 2; i++) {
        str[i][strlen(str[i]) - 1] = '\0';
    }
    return 0;
}
