#include <stdio.h>
#include <string.h>
#include <regex.h>

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
  while(search_tmp[ct] != 0) {
  	ct++;
  } 
  ct--;
  char *search[ct];
  for(int i = 0; i < ct; i++) {
  	search[i] = search_tmp[i];
  } 
  
  /* main file searching, iterates through each file and searches through searches array */
  int i = 0;
  while(files[i] != 0) {
  	FILE* file = fopen(files[i], "r")
  	printf("%s\n\n", files[i]);
  	for(int j = 0; j < ct; j++) {
  		printf("%s\n\n\n", search[j]);
  		regex_t regex;
  		regematch_t pmatch[1];

  		if(regcomp(&regex, search[j], REG_NEWLINE))
  			exit(EXIT_FAILURE);

  		
  		for (unsigned int i = 0;; i++) {
    		if (regexec(&regex, file, sizeof(pmatch)/sizeof(pmatch[0]), pmatch, 0))
      		break;

      	
  	}
  	fclose(file);
  }
}
