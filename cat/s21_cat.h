#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#define MAX_LEN 30

struct flags {
    int b, e, n, s, t, v;
} f1;

struct option long_options[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {NULL, 0, NULL, 0}};

int cat(int p, char *argv[]);
int opt_parser(int argc, char **argv);

#endif  // SRC_CAT_S21_CAT_H_
