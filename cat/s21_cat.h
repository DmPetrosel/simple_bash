#ifndef S21_CAT_H_
#define S21_CAT_H_
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int b;
  int e;
  int E;
  int n;
  int s;
  int t;
  int T;
  int v;
} options;

int get_flags(options *opt, int argc, char **argv);
void non_print(options opt, char *str, int j, int *new_line);
void printing_letters(options opt, char *str, int j, int *count_squeeze,
                      int *new_line);
void go_through_line(options opt, int *new_line, int bs, int *count, char *str,
                     int *count_squeeze);
#endif