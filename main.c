#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  /* main file searching, iterates through each file and searches through
   * searches array */
  for (int i = 0; i < files_index; i++) {
    printf("File: %s\n", files[i]);
    for (int j = 0; j < search_index; j++) {
      FILE *file = fopen(files[i], "r");
      for (int k = 0; I && k < strlen(search[j]); k++) {
        search[j][k] = tolower(search[j][k]);
      }

      printf("Search term: %s\n", search[j]);
      regex_t regex;

      if (regcomp(&regex, search[j], REG_EXTENDED | REG_NOSUB)) {
        exit(EXIT_FAILURE);
      }
      char current_line[500];
      int line_number = 1;
      while (fgets(current_line, sizeof(current_line), file) != NULL) {
        char tmp_line[strlen(current_line)];
        if (I) {
          for (int k = 0; k < strlen(current_line); k++) {
            tmp_line[k] = tolower(current_line[k]);
          }
        }
        int reti;
        if (I) {
          reti = regexec(&regex, tmp_line, 0, NULL, 0);
        } else {
          reti = regexec(&regex, current_line, 0, NULL, 0);
        }
        if (!reti) {
          if (N) {
            printf("%d: ", line_number);
          }
          printf("%s", current_line);
        } else if (reti == REG_NOMATCH) {
        } else {
          regerror(reti, &regex, current_line, sizeof(current_line));
          fprintf(stderr, "Regex match failed: %s\n", current_line);
          exit(1);
        }
        line_number++;
      }
      regfree(&regex);
      fclose(file);
    }
  }
}
