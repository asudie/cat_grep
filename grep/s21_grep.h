#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLENGTH 9999

typedef struct flags {
  int e, i, v, c, l, n, h, s, f, o, print_fname;
} f1;

int opt_parser(int argc, char **argv, f1 *flags, char sample_list[]);
int patterns(char *sample, char *file_name);
int grep_start(f1 *flag, int argc, char **argv, char *sample_list);
int escape_char(char *sample);
int open_file(f1 *flags, char *sample, char *file_name);
int grep_file(f1 *flags, FILE *fp, regex_t reg, char *file);
int print_match(FILE *fp, int nline, int status, f1 *flags, char *text,
regmatch_t *pmatch, char *file);

#endif  // SRC_GREP_S21_GREP_H_
