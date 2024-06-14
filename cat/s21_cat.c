#define _POSIX_C_SOURCE 201709L
#include "s21_cat.h"

int main(int argc, char **argv) {
  options opt = {0, 0, 0, 0, 0, 0, 0, 0};
  int count = 1;
  int count_squeeze = 0;
  if (!get_flags(&opt, argc, argv)) {
    int quantity_of_files = argc - optind;
    for (int i = 0; i < quantity_of_files; i++) {
      FILE *file;
      if ((file = fopen(argv[optind], "r")) == NULL) {
        fprintf(stderr, "cat: %s: No such file or directory\n", argv[optind++]);
        optind++;
        continue;
      }
      size_t bsize = 0;
      char *str = NULL;
      int bs = 0;
      int new_line = 0;
      while ((bs = getline(&str, &bsize, file)) != -1) {
        if (new_line) count++;
        go_through_line(opt, &new_line, bs, &count, str, &count_squeeze);
      }
      free(str);
      optind++;
      fclose(file);
    }
    return 0;
  } else {
    return -1;
  }
}
void printing_letters(options opt, char *str, int j, int *count_squeeze,
                      int *new_line) {
  if (str[j] == '\n' && opt.e)
    ;
  else if (!opt.v && (!opt.s || (*count_squeeze == 0 && opt.s)) && j == 0 &&
           str[0] == '\n' && !opt.e) {
    printf("%c", str[j]);
    (*count_squeeze)++;
  } else if (!opt.v && j != 0 && !(opt.e && opt.E && str[j + 1] == '\0')) {
    printf("%c", str[j]);
    *count_squeeze = 0;
  } else if (!opt.v && j != 0 && !(opt.e && str[j + 1] == EOF)) {
    printf("%c", str[j]);
    *count_squeeze = 0;
  } else if (j == 0 && str[j] != '\n') {
    printf("%c", str[j]);
    *count_squeeze = 0;
  }
  if (str[j] == '\n') *new_line = 1;
}

void go_through_line(options opt, int *new_line, int bs, int *count, char *str,
                     int *count_squeeze) {
  for (int j = 0; j < bs; j++) {
    if (!opt.b && opt.n && (*new_line || *count == 1)) {
      if (j == 0) printf("% 6d\t", *count);
    }

    if (opt.b) {
      if (j == 0 && str[0] != '\n' && (*new_line || *count == 1))
        printf("% 6d\t", *count);
      else if (j == 0 && str[0] == '\n' && (*new_line || *count == 1))
        (*count)--;
    }
    *new_line = 0;
    if (str[j] == '\t' && opt.t)
      printf("^I");
    else if (opt.v) {
      non_print(opt, str, j, new_line);
    } else {
      printing_letters(opt, str, j, count_squeeze, new_line);
    }
    if (str[j] == '\n' && (opt.e || opt.E) &&
        ((!opt.s || *count_squeeze == 0))) {
      printf("$\n");
      *new_line = 1;
    }
  }
}

void non_print(options opt, char *str, int j, int *new_line) {
  unsigned char uc = (unsigned char)str[j];

  if (str[j] == '\n' && !opt.e) {
    printf("\n");
    *new_line = 1;
  } else if (str[j] == '\t' && !opt.t && !opt.T) {
    printf("\t");
  } else if (uc < 32 && uc != '\n') {
    printf("^%c", uc + 64);
  } else if (uc == 127) {
    printf("^?");
  } else if (uc >= 128 && uc <= 159) {
    printf("M-^%c", uc - 64);
  } else if (uc >= 160 && uc < 255) {
    printf("M-%c", uc - 128);
  } else if (uc == 255) {
    printf("M-^?");
  } else if (opt.e && uc == '\n')
    *new_line = 1;
  else
    printf("%c", uc);
}

int get_flags(options *opt, int argc, char **argv) {
  int err = 0;
  int option_index = 0;
  int c = 0;
  struct option long_options[] = {{"number-nonblank", no_argument, 0, 'b'},
                                  {"number", no_argument, 0, 'n'},
                                  {"squeeze-blank", no_argument, 0, 's'}};
  while (c != -1) {
    c = getopt_long(argc, argv, "sbentETv", long_options, &option_index);
    if (opt->s && c == 'n') {
      c = 'b';
    }
    switch (c) {
      case 's':
        opt->s = 1;
        break;
      case 'b':
        opt->b = 1;

        break;
      case 'n':
        opt->n = 1;
        break;
      case 't':
        opt->t = 1;
        opt->v = 1;
        break;
      case 'T':
        opt->t = 1;
        opt->v = 0;
        break;
      case 'e':
        opt->e = 1;
        opt->v = 1;
        break;
      case 'E':
        opt->E = 1;
        opt->e = 1;
        opt->v = 0;
        break;
      case 'v':
        opt->v = 1;
        break;
      case '?':
        err = 1;
    }
    if (c == 'b') opt->b = 1;
    if (c == 's') opt->s = 1;
  }
  return err;
}