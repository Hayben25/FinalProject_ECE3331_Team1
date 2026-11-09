#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

  bool I = false;
  bool V = false;
  bool O = false;

  char *search[argc - 1];
  int index = 0;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      for (int j = 0; j < sizeof(argv[i]); j++) {
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
        }
      }
    } else {
      if (strstr(argv[i], ".txt") == NULL) {
        search[index] = argv[i];
        index++;
        printf("%s is not a text file!\n", search[index - 1]);
      } else {
        if (argv[i] - strstr(argv[i], ".txt") + strlen(argv[i]) == 4) {
          printf("%s is a text file!\n", argv[i]);
        }
      }
    }
  }
}
