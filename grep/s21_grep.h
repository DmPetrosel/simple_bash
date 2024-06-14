#ifndef S21_GREP_H_
#define S21_GREP_H_
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SBUF 10

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int cflags;
} options;

int get_flags(options *opt, int argc, char **argv, char **patt, int *cnt);
// void getFilesIndexes(int * indexes_of_files, int * lenIndFile, int argc);
void execute_program(int argc, char **argv, char *patt, options opt,
                     int quantOfFiles);
void flag_o(regex_t *reegex, FILE *file, options opt, int quantityOfFiles,
            char **argv);
// void getPattern(int argc, char **argv, char **patterns);
// void Epattern(char ** patterns, int countE,char* patt);
int get_file_patterns(char **patt, int *cnt, char *filename);
// void freePatterns(char ** patterns, int countE);
int add_pattern(char **patt, char *current_pattern, int *cnt);
void printing_matching_lines(FILE *file, int line_numb, int quantity_of_files,
                             char **argv, options opt, regex_t *reegex);

#endif