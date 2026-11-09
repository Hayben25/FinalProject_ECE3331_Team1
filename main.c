#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

  /* variables for command line arguments */
  bool I = false;
  bool V = false;
  bool O = false;

  /* array for search terms */
  char *search_tmp[argc - 1];
  int search_index = 0;
  /* array for files */
  char *files_tmp[argc - 1];
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
        }
      }
    }

    else { /* file vs search detection */
      FILE *file;
      if ((file = fopen(argv[i], "r")) != NULL) {
      	files_tmp[files_index] = argv[i];
      	files_index++;
        fclose(file);
      } else {
      	search_tmp[search_index] = argv[i];
      	search_index++;
      }
    }
  }
  int ct = 0;
  for(int i = 0; i < argc-1; i++) {
  	if(search_tmp[i] == 0) {
  		break;
  	}
  	ct++;
  } 
  printf("searches:");
  char *search[ct];
  for(int i = 0; i < ct-1; i++) {
  	search[i] = search_tmp[i];
  	printf(" %s", search[i]);
  } 
  ct = 0;
  for(int i = 0; i < argc-1; i++) {
  	if(files_tmp[i] == 0) {
  		break;
  	}
  	ct++;
  }
  printf("\nfiles: ", ct);
  char *files[ct];
  for(int i = 0; i < ct; i++) {
  	files[i] = files_tmp[i];
  	printf(" %s", files[i]);
  }
}
