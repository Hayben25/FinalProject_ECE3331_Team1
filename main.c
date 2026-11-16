#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

  /* variables for command line arguments */
  bool I = false;
  bool V = false;
  bool O = false;
  bool C = false;

  /* array for search terms */
  char *search_tmp[argc - 1];
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
      	search_tmp[search_index] = argv[i];
      	search_index++;
      }
    }
  }
  /* puts searches tmp array into a better fitting one */
  int ct = 0;
  for(int i = 0; i < argc-1; i++) {
  	if(search_tmp[i] == 0) { /* checks if at end of searches */
  		break;
  	}
  	ct++;
  } 
  ct--;
  char *search[ct];
  for(int i = 0; i < ct; i++) {
  	search[i] = search_tmp[i];
  } 
  
  /* main file searching, iterates through each file and searches through searches array */
  for(int i = 0; i < argc-1; i++) {
  	if(files[i] == 0) { /* checks if at end of files */
  		break;
  	}
  	FILE* file = fopen(files[i], "r")
  	printf("%s\n\n", files[i]);
  	for(int j = 0; j < ct; j++) {
  		printf("%s\n\n\n", search[j]);
  		if(C) {
  			
  		}
  	}
  	fclose(file);
  }
}
