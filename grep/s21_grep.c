#include "s21_grep.h"

int main(int argc, char *argv[]) {
  f1 flags;
  memset(&flags, 0, sizeof(flags));
  int result = 0;
  char sample_list[BUFLENGTH] = {0};
  result = opt_parser(argc, argv, &flags, sample_list);
  if ((argc >= 3) && result) {
    result = grep_start(&flags, argc, argv, sample_list);
  } else if (!result) {
    fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], optarg);
  }
  return result == 1 ? 0 : 1;
}

int opt_parser(int argc, char **argv, f1 *flags, char sample_list[]) {
  int num_samples = 0;
  int opt;
  int result = 1;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    if (opt == 'e' || opt == 'f') {
      int n = 0;
      if (num_samples > 0) {
        strcat(sample_list, "|");
      }

      if (opt == 'e') {
        flags->e = 1;
        if (strlen(sample_list) + strlen(optarg) < BUFLENGTH) {
          strcat(sample_list, optarg);
        } else {
          result = 0;
          break;
        }
        n = 1;
      } else if (opt == 'f') {
        flags->f = 1;
        n = patterns(sample_list + strlen(sample_list), optarg);
        if (n == -1) {
          result = 0;
          break;
        }
      }
      num_samples += n;
    } else if (opt == 'i') {
      flags -> i = 1;
    } else if (opt == 'v') {
      flags -> v = 1;
    } else if (opt == 'c') {
      flags -> c = 1;
    } else if (opt == 'l') {
      flags -> l = 1;
    } else if (opt == 'n') {
      flags -> n = 1;
    } else if (opt == 'h') {
      flags -> h = 1;
    } else if (opt == 's') {
      flags -> s = 1;
    } else if (opt == 'o') {
      flags -> o = 1;
    } else {
      result = 0;
    }
  }
  // printf("e%d, i%d, v%d,c%d, l%d, n%d, h%d, s%d, f%d, o%d\n", flags->e, flags->i,
  //        flags->v, flags->c, flags->l, flags->n, flags->h, flags->s, flags->f, flags->o);

  return result;
}

int patterns(char *sample, char *file_name) {
  FILE *fp;
  fp = fopen(file_name, "r");
  int i = 0, num_samples = 0;
  if (fp == NULL) {
    i = -1;
  } else {
    int ch;
    while ((ch = fgetc(fp)) != EOF && i < BUFLENGTH) {
      if (ch == 13 || ch == 10) {
        sample[i++] = '|';
        num_samples++;
      } else {
        sample[i++] = ch;
      }
    }
    if (i < BUFLENGTH) {
      if (sample[i - 1] == '|') {
        sample[i - 1] = '\0';
      }
    } else {
      i = -1;
    }
    fclose(fp);
  }
  return i != -1 ? num_samples : -1;
}

int grep_start(f1 *flags, int argc, char **argv, char *sample_list) {
  int result = 1;
  char sample[BUFLENGTH] = {0};
  if (!flags -> f && !flags -> e) {
    snprintf(sample, BUFLENGTH, "%s", argv[optind++]);
  }
  if (flags -> f || flags -> e) {
    snprintf(sample, BUFLENGTH, "%s", sample_list);
  }
  if (escape_char(sample)) {
    int file_num = (argc - optind);  // if argv = 3 then file index will be 2 so 3-2=1 which means 1 file
    if (file_num > 1 && !flags -> h && !flags -> l) {
      flags -> print_fname = 1;
    }
    for (int i = optind; i < argc; i++) {
      result = open_file(flags, sample, argv[i]);
      if (!result && !flags -> s) {
        fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], argv[i]);
      }
    }
  } else {
    result = 0;
  }
  return result;
}

int escape_char(char *sample) {
  int result = 1;
  char tmp[BUFLENGTH];
  if (sample) {
    int i = 0, j = 0;
    strcpy(tmp, sample);
    while (tmp[j] && i < BUFLENGTH) {
      if (strchr("[]/^$.?*+(){}", tmp[j])) {
        if (j > 0 && tmp[j - 1] == '\\') {
            sample[i++] = tmp[j++];
        } else {
          sample[i++] = '\\';
          sample[i++] = tmp[j++];
        }
      } else {
        sample[i++] = tmp[j++];
      }
    }
    if (i == BUFLENGTH) {
      result = 0;
    } else {
      sample[i] = '\0';
    }

  } else {
    result = 0;
  }
  return result;
}

int open_file(f1 *flags, char *sample, char *file_name) {
  int cflags = (flags->i) ? REG_ICASE | REG_EXTENDED : REG_EXTENDED;
  int result = 1;
  regex_t reg;
  FILE *fp;
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    result = 0;
  } else {
    if (regcomp(&reg, sample, cflags)) {
      result = 0;
    } else {
      result = grep_file(flags, fp, reg, file_name);
      regfree(&reg);
      fclose(fp);
    }
  }
return result;
}

int grep_file(f1 *flags, FILE *fp, regex_t reg, char *file) {
  int result = 1;
  char text[BUFLENGTH] = {0};
  regmatch_t pmatch[1];  // 1 means extended -> not full match included
  int line_matches = 0, nline = 1;
  while (fgets(text, BUFLENGTH - 1, fp) != NULL) {
    int status = regexec(&reg, text, 1, pmatch, 0);  // compares regex with str, match = 0
    if (status == 0 || status == REG_NOMATCH) {
      line_matches += print_match(fp, nline, status, flags, text, pmatch, file);
      nline++;
    } else {
      result = 0;
      break;
    }
  }
  if (result) {
    if (flags -> l && line_matches > 0) {
      printf("%s\n", file);
    }
    if (flags -> c && !flags -> l && flags -> print_fname) {
      printf("%s:", file);
    }
    if (flags ->c && !flags -> l) {
      printf("%d\n", line_matches);
    }
  }
  return result;
}


int print_match(FILE *fp, int nline, int status, f1 *flags, char *text,
regmatch_t *pmatch, char *file) {
  int match = 0;
  if (status == 0 && !flags -> v) {
    match = 1;
  }
  if (status == REG_NOMATCH && flags -> v) {
    match = 1;
  }
  if (match && !flags -> l && !flags -> c && flags -> print_fname && file != NULL) {
    printf("%s:", file);
  }
  if (match && !flags -> l && !flags -> c && flags -> n) {
    printf("%d:", nline);
  }
  if (match && !flags -> l && !flags -> c && !flags -> o) {
    if (feof(fp) && text[strlen(text)] != '\n') {  // feof > 0 if end of file
      strcat(text, "\n");
    }
    if (!flags -> v) {  // Определяет, что вывод не в поток ошибок
      printf("%.*s%.*s%s", (int)pmatch[0].rm_so, text,
      (int)pmatch[0].rm_eo - (int)pmatch[0].rm_so, text
             + (int)pmatch[0].rm_so,
      text + (int)pmatch[0].rm_eo);
    } else {
      printf("%s", text);
    }
  }
  if (flags -> o && match) {
      printf("%.*s\n", (int)pmatch[0].rm_eo - (int)pmatch[0].rm_so,
             text + (int)pmatch[0].rm_so);
  }
return match;
}

