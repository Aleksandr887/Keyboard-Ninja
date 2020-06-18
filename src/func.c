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

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void print(int correct, int uncorrect, double time, char* str[])
{
    printf("%s %d\n%s %d\n%s %lf\n",
           str[4],
           correct,
           str[5],
           uncorrect,
           str[6],
           time);
    while (1) {
        char sett[40];
        printf("%s\n", str[9]);
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

int set_lang(char lang[], FILE** f, char* str[])
{
    if (strcmp(lang, "rus") == 0) {
        *f = fopen("rus.txt", "r");
    } else if (strcmp(lang, "eng") == 0) {
        *f = fopen("eng.txt", "r");
    }
    language(lang, str);
    return 0;
}

void language(char lang[], char* str[])
{
    char lan[4];
    int max_len = -1;
    int amount = 0;

    FILE* conf = fopen("lang.cfg", "r");
    max_len_amount_lines(&amount, &max_len, conf);
    max_len += 2;
    while (strcmp(lan, lang) != 0) {
        fgets(lan, 4, conf);
    }
    char* buf = malloc(max_len * sizeof(char));
    /*l->hello = malloc(max_len * sizeof(char));
    fgets(l->hello, max_len, conf);
    fgets(l->hello, max_len, conf);

    l->getready = malloc(max_len * sizeof(char));
    fgets(l->getready, max_len, conf);

    l->correct = malloc(max_len * sizeof(char));
    fgets(l->correct, max_len, conf);

    l->uncorrect = malloc(max_len * sizeof(char));
    fgets(l->uncorrect, max_len, conf);

    l->co = malloc(max_len * sizeof(char));
    fgets(l->co, max_len, conf);

    l->un = malloc(max_len * sizeof(char));
    fgets(l->un, max_len, conf);

    l->time = malloc(max_len * sizeof(char));
    fgets(l->time, max_len, conf);

    l->write = malloc(max_len * sizeof(char));
    fgets(l->write, max_len, conf);

    l->sett = malloc(max_len * sizeof(char));
    fgets(l->sett, max_len, conf);

    l->message_sett = malloc(max_len * sizeof(char));
    fgets(l->message_sett, max_len, conf);

    l->close = malloc(max_len * sizeof(char));
    fgets(l->close, max_len, conf);

    l->dunno = malloc(max_len * sizeof(char));
    fgets(l->dunno, max_len, conf);*/
    fgets(buf, max_len, conf);
    for (int i = 0; i < (amount - 2) / 2; i++) {
        str[i] = malloc(max_len * sizeof(char));
        fgets(str[i], max_len, conf);
    }
    rm_last_sym(str, amount);
    fclose(conf);
    free(buf);
}

void rm_last_sym(char* str[], int amount)
{
    for (int i = 0; i < (amount - 2) / 2; i++) {
        str[i][strlen(str[i]) - 1] = '\0';
    }
    /*l->hello[strlen(l->hello) - 1] = '\0';
    l->getready[strlen(l->getready) - 1] = '\0';
    l->correct[strlen(l->correct) - 1] = '\0';
    l->uncorrect[strlen(l->uncorrect) - 1] = '\0';
    l->co[strlen(l->co) - 1] = '\0';
    l->un[strlen(l->un) - 1] = '\0';
    l->time[strlen(l->time) - 1] = '\0';
    l->write[strlen(l->write) - 1] = '\0';
    l->sett[strlen(l->sett) - 1] = '\0';
    l->message_sett[strlen(l->message_sett) - 1] = '\0';
    l->close[strlen(l->close) - 1] = '\0';
    l->dunno[strlen(l->dunno) - 1] = '\0';*/
}
