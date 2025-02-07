#include "s21_cat.h"

int main(int argc, char *argv[]) {
  if (opt_parser(argc, argv) == 0) {
    int p = optind;
    while (p < argc && argc > 1) {
      cat(p, argv);
      p++;
    }
  } else {
    fprintf(stderr, "\nusage: s21_cat [-benstuv] [file ...]");
  }
  return 0;
}

int cat(int p, char *argv[]) {
  FILE *src = NULL;
  if ((src = fopen(argv[p], "r")) == NULL) {
    fprintf(stderr, "s21_cat: %s: No such file or directory", argv[p]);
  } else {
    int last_char = '\n', ent_count = 1;
    int count_str = 1;
    while (1) {
      int tmp = getc(src);
      if (tmp != '\n') {
        ent_count = 1;
      }
      if (tmp == EOF) {
        break;
      }
      if (f1.s && last_char == '\n' && tmp == '\n') {
        if (ent_count) {
          ent_count--;
        } else {
          continue;
        }
      }
      if (f1.b && last_char == '\n' && tmp != '\n') {
        printf("%6d\t", count_str);
        count_str++;
      } else if (f1.n && last_char == '\n') {
        printf("%6d\t", count_str);
        count_str++;
      }

      if (f1.t && tmp == '\t') {
        printf("^I");
        last_char = tmp;
        continue;
      }

      if (f1.e && tmp == '\n') {
        printf("$");
      }

      if ((f1.v && (tmp == 127)) || (tmp < 32 && tmp != 10 && tmp != 9)) {
        if (tmp > 127 && tmp < 160) {
          tmp -= 127;
          tmp += 63;
          printf("M-");
        }

        if (tmp == 127) {
          tmp -= 64;
          printf("^");
        } else if (tmp >= 0 && tmp < 32) {
          tmp += 64;
          printf("^");
        }
      }

      printf("%c", tmp);
      last_char = tmp;
    }
    fclose(src);
  }
  return 0;
}



int opt_parser(int argc, char **argv) {
  f1.b = 0, f1.e = 0, f1.n = 0, f1.s = 0, f1.t = 0;

  int opt;
  while ((opt = getopt_long(argc, argv, "beEvnst", long_options, NULL)) != -1) {
    switch (opt) {
      case 'b':
        f1.b = 1;
        break;
      case 'e':
        f1.e = 1;
        break;
      case 'v':
        f1.v = 1;
        break;
      case 'E':
        f1.e = 1;
        break;
      case 'n':
        f1.n = 1;
        break;
      case 's':
        f1.s = 1;
        break;
      case 't':
        f1.t = 1;
        break;
    }
    if (f1.b) {
      f1.n = 0;
    }
  }
  //   printf("b%d, e%d, n%d,s%d, t%d\n", f1.b, f1.e, f1.n, f1.s, f1.t);

  return 0;
}
