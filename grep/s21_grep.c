#define _POSIX_C_SOURCE 201709L
#include "s21_grep.h"

int main(int argc, char **argv) {
  char *patt = NULL;
  int cnt = 1, err = 0;
  options opt = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int quantityOfFiles = 0;

  if (!get_flags(&opt, argc, argv, &patt, &cnt) && patt != 0) {
    execute_program(argc, argv, patt, opt, quantityOfFiles);
  } else {
    err = 1;
  }
  free(patt);
  return err;
}
int add_pattern(char **patt, char *current_pattern, int *cnt) {
  int err = 0;
  char *temp;
  if (*patt != NULL) {
    while (strlen(*patt) + 5 + strlen(current_pattern) >=
           (size_t)(SBUF * (*cnt))) {
      (*cnt)++;
    }
  }
  if (*patt == NULL) {
    while (5 + strlen(current_pattern) >= (size_t)(SBUF * (*cnt))) {
      (*cnt)++;
    }
    temp = (char *)calloc(SBUF * (*cnt), sizeof(char));
  } else {
    temp = (char *)realloc(*patt, SBUF * (*cnt) * sizeof(char));
  }
  if (temp == NULL) {
    fprintf(stderr, "Allocation memory error\n cnt = %d\n", (*cnt));
    err = 1;
  } else {
    *patt = temp;
  }
  if (strlen(*patt) != 0) strcat(*patt, "|");
  strcat(*patt, "(");
  strcat(*patt, current_pattern);
  strcat(*patt, ")");
  return err;
}

void execute_program(int argc, char **argv, char *patt, options opt,
                     int quantity_of_files) {
  FILE *file;
  char *str = NULL;
  size_t buffsize = 0;
  regex_t reegex;
  regmatch_t match;

  quantity_of_files = argc - optind;
  int flagLYes = 0;
  regcomp(&reegex, patt, opt.cflags);
  for (int indFile = 0; indFile < quantity_of_files; indFile++) {
    flagLYes = 0;
    if (!(file = fopen(argv[optind], "r"))) {
      if (!opt.s)
        fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                argv[optind]);
      optind++;
      continue;
    }
    int mtch = -1;
    if (opt.l) {
      while (getline(&str, &buffsize, file) != -1 && flagLYes != 1) {
        mtch = regexec(&reegex, str, 1, &match, 0);
        if ((!opt.v && mtch == 0) || ((opt.v && mtch != 0))) {
          flagLYes = 1;
        }
      }
      if (flagLYes) {
        printf("%s\n", argv[optind++]);
        continue;
      }
    }

    int line_numb = 0;

    printing_matching_lines(file, line_numb, quantity_of_files, argv, opt,
                            &reegex);

    fclose(file);
    optind++;
  }
  free(str);
  regfree(&reegex);
}

void printing_matching_lines(FILE *file, int line_numb, int quantity_of_files,
                             char **argv, options opt, regex_t *reegex) {
  int count = 0;
  char *str = NULL;
  size_t buffsize = 0;
  int mtch = -1;
  regmatch_t match;
  rewind(file);
  while (getline(&str, &buffsize, file) != -1) {
    line_numb++;
    mtch = regexec(reegex, str, 1, &match, 0);
    if (mtch == 0 && (opt.c)) {
      count++;
    }

    if (!opt.o && !opt.c &&
        ((opt.v && mtch != 0) || ((opt.n && !opt.v) && mtch == 0) ||
         (!opt.v && mtch == 0))) {
      int j = 0;
      if ((opt.n && opt.h) || (opt.n && quantity_of_files == 1))
        printf("%d:", line_numb);
      else if (opt.n && quantity_of_files > 1)
        printf("%s:%d:", argv[optind], line_numb);
      else if (quantity_of_files > 1 && !opt.c && !opt.h)
        printf("%s:", argv[optind]);
      if (!(opt.c || opt.o)) {
        while (str[j] != '\0' && str[j] != '\n') {
          printf("%c", str[j]);
          j++;
        }
        printf("\n");
      }
    }
  }
  if (opt.o && !opt.c) {
    if (!opt.v) flag_o(reegex, file, opt, quantity_of_files, argv);
  } else if (opt.c) {
    if (quantity_of_files > 1 && !opt.h) printf("%s:", argv[optind]);
    if (opt.v) {
      printf("%d\n", line_numb - count);
    } else
      printf("%d\n", count);
  }
  free(str);
}

void flag_o(regex_t *reegex, FILE *file, options opt, int quantityOfFiles,
            char **argv) {
  regmatch_t match;
  size_t buffsize = 0;
  char *str;
  rewind(file);
  int count = 0;
  while (getline(&str, &buffsize, file) != -1) {
    count++;
    if (regexec(reegex, str, 1, &match, 0) == 0) {
      if (!opt.h && quantityOfFiles > 1)
        printf("%s:", argv[optind]);
      else if (!opt.h && quantityOfFiles > 1)
        printf("%s:", argv[optind]);
      if (opt.n) printf("%d:", count);
      printf("%.*s\n", (int)(match.rm_eo - match.rm_so), str + match.rm_so);
      char *remain = str + match.rm_eo;
      while (regexec(reegex, remain, 1, &match, 0) == 0) {
        if (!opt.h && quantityOfFiles > 1)
          printf("%s:", argv[optind]);
        else if (!opt.h && quantityOfFiles > 1)
          printf("%s:", argv[optind]);
        if (opt.n) printf("%d:", count);
        printf("%.*s\n", (int)(match.rm_eo - match.rm_so),
               remain + match.rm_so);
        remain = remain + match.rm_eo;
      }
    }
  }
  free(str);
}

int get_flags(options *opt, int argc, char **argv, char **patt, int *cnt) {
  int err = 0;
  optind = 0;
  int c;
  opt->cflags |= REG_EXTENDED;
  while ((c = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (c) {
      case 'e':

        err |= add_pattern(patt, optarg, cnt);
        opt->e = 1;

        break;
      case 'i':
        opt->i = 1;
        opt->cflags |= REG_ICASE;
        break;
      case 'v':
        opt->v = 1;
        break;
      case 'o':
        opt->o = 1;
        break;
      case 'c':
        opt->c = 1;
        break;
      case 's':
        opt->s = 1;
        break;
      case 'n':
        opt->n = 1;
        break;
      case 'f':
        opt->f = 1;
        err |= get_file_patterns(patt, cnt, optarg);
        break;
      case 'l':
        opt->l = 1;
        break;
      case 'h':
        opt->h = 1;
        break;
      case '?':
        err = 1;
        break;
      default:
        break;
    }
  }
  if (!opt->e && !opt->f && optind < argc) {
    err |= add_pattern(patt, argv[optind], cnt);
    optind++;
  }
  return err;
}
int get_file_patterns(char **patt, int *cnt, char *filename) {
  int err = 0;
  FILE *pfile = NULL;
  if (!(pfile = fopen(filename, "r"))) {
    fprintf(stderr, "s21grep: %s: No such file or directory\n", filename);
    err = 1;
  } else {
    char *s = NULL;
    size_t size = 0;
    char *ss = NULL;
    while (getline(&s, &size, pfile) != -1) {
      if (strlen(s) >= 1 && s[strlen(s) - 1] == '\n') {
        ss = strndup(s, strlen(s) - 1);
      } else
        strcpy(ss, s);
      if (strlen(ss) != 0) add_pattern(patt, ss, cnt);
    }
    free(ss);
    free(s);
    fclose(pfile);
  }
  return err;
}