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
  int i = 0;
  // while (files[i] != "") {
  FILE *file = fopen(files[i], "r");
  printf("File: %s\n", files[i]);
  for (int j = 0; j < search_index; j++) {
    printf("Search term: %s\n", search[j]);
    regex_t regex;

    if (regcomp(&regex, search[j], REG_EXTENDED | REG_NOSUB)) {
      exit(EXIT_FAILURE);
    }
    char current_line[500];
    while (fgets(current_line, sizeof(current_line), file) != NULL) {
      int reti = regexec(&regex, current_line, 0, NULL, 0);
      if (!reti) {
        printf("%s", current_line);
      } else if (reti == REG_NOMATCH) {
      } else {
        regerror(reti, &regex, current_line, sizeof(current_line));
        fprintf(stderr, "Regex match failed: %s\n", current_line);
        exit(1);
      }
    }
    regfree(&regex);
  }
  i++;
  fclose(file);
  //}
}
