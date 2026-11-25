#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define countof(a) (sizeof(a) / sizeof(*(a)))
/* for colored output */
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_BLUE "\x1b[34m"

int main(int argc, char *argv[]) {

  /* variables for command line arguments */
  bool I = false;
  bool V = false;
  bool N = false;
  bool O = false;
  bool C = false;

  /* array for search terms */
  char *search[argc - 1];
  int search_index = 0;
  /* array for files */
  char *files[argc - 1];
  int files_index = 0;

  /* command line argument organization loop */
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') { /* takes specific arguments (ex. -v, -i, -iv) */

      for (int j = 0; j < strlen(argv[i]); j++) {
        switch (argv[i][j]) {
        case 'i':
          I = true;
          break;
        case 'v':
          V = true;
          break;
        case 'o':
          O = true;
          break;
        case 'c':
          C = true;
          break;
        case 'n':
          N = true;
          break;
        }
      }
    }

    else { /* file vs search detection */
      FILE *file;
      if ((file = fopen(argv[i], "r")) != NULL) {
        files[files_index] = argv[i];
        files_index++;
        fclose(file);
      } else {
        search[search_index] = argv[i];
        search_index++;
      }
    }
  }
  if (V && O) {
    fprintf(stderr, ANSI_COLOR_RED
            "-v and -o used together, exiting program\n" ANSI_COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  char *v_list[500];
  int v = 0;
  /* main file searching, iterates through each file and searches through
   * searches array */
  for (int i = 0; i < files_index; i++) {
    printf(ANSI_COLOR_GREEN "File: %s\n" ANSI_COLOR_RESET, files[i]);
    for (int j = 0; j < search_index; j++) {
      FILE *file = fopen(files[i], "r");
      for (int k = 0; I && k < strlen(search[j]); k++) {
        search[j][k] = tolower(search[j][k]);
      }

      printf(ANSI_COLOR_MAGENTA "Search term: %s\n" ANSI_COLOR_RESET,
             search[j]);
      regex_t regex;
      regmatch_t pmatch[1];
      regoff_t off, len;

      if (regcomp(&regex, search[j], REG_EXTENDED)) {
        exit(EXIT_FAILURE);
      }
      char current_line[500];
      int line_number = 1;    /* if -n is selected */
      int count_selected = 0; /* if -c is selected */
      while (fgets(current_line, sizeof(current_line), file) !=
             NULL) { /* loops through every line in a file */
        char tmp_line[strlen(current_line)];
        if (I) { /* makes a tmp array of lowercase lines if -i is selected */
          for (int k = 0; k < strlen(current_line); k++) {
            tmp_line[k] = tolower(current_line[k]);
          }
        }
        int reti;
        if (I) { /* uses tmp_line so all letters are lowercase if -i is selected
                  */
          reti = regexec(&regex, tmp_line, countof(pmatch), pmatch, 0);
        } else {
          reti = regexec(&regex, current_line, countof(pmatch), pmatch, 0);
        }
        if (!reti) { /* if the regex is found */
          if (N) {   /* if -n is selected the current line number is printed */
            printf("%d: ", line_number);
          }
          if (C) { /* if -c is selected the count of regexs found is incremented
                    */
            count_selected++;
          }
          if (O) {
            char *s = current_line;
            while (true) {
              if (regexec(&regex, s, countof(pmatch), pmatch, REG_EXTENDED)) {
                break;
              }

              len = pmatch[0].rm_eo - pmatch[0].rm_so;
              printf("%.*s\n", len, s + pmatch[0].rm_so);

              s += pmatch[0].rm_eo;
            }
          } else {
            if (V) {
              bool copy = false;
              for (int k = 0; k < v; k++) {
                if (strcmp(v_list[k], current_line) == 0) {
                  copy = true;
                  break;
                }
              }
              if (!copy || v == 0) {
                v_list[v] = current_line;
                printf("%s", v_list[v]);
                v++;
              }
            } else {
              printf("%s", current_line);
            }
          }
        } else if (reti == REG_NOMATCH) { /* if the regex is not found */
        } else { /* if there is an error with the regex */
          regerror(reti, &regex, current_line, sizeof(current_line));
          fprintf(stderr,
                  ANSI_COLOR_RED "Regex match failed: %s\n" ANSI_COLOR_RESET,
                  current_line);
          exit(EXIT_FAILURE);
        }
        if (N) {
          line_number++;
        } /* if -n is chosen this keeps track of the line number */
      }
      if (C) {
        printf(ANSI_COLOR_BLUE "%s had %d selected lines\n" ANSI_COLOR_RESET,
               files[i], count_selected);
      }
      regfree(&regex);
      fclose(file);
    }
  }
}
