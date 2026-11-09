#include <stdio.h>

int main(int argc, char *argv[]) {
	bool I = false;
	bool V = false;
	bool O = false;
	for(int i = 0; i < argc; i++) {
		if (argv[i][0] == '-') {
			printf("This one: %s\n", argv[i]);
			for(int j = 0; j < argv[i](); j++) {
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
		}
	}
	if(I) {
		printf("I true");
	}
	if(V) {
		printf("V true");
	}
	if(O) {
		printf("O true");
	}
}
