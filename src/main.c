#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> //for checking file size

#define FILENAME "instructions.txt"

char MEMORY[1024*1024] = {0}; //1mb
char *ptr = MEMORY;

char *file_contents = NULL;
char **loop_beginnings = NULL;

int load_file(const char *path) {
	struct stat st;
	
	stat(path, &st);
	file_contents = malloc((st.st_size+1) * sizeof(char));
	
	if(file_contents == NULL) {
		fputs("Error allocating memory for instructions", stdout);
		return 1;
	}

	FILE *f = fopen(path, "rb");
		fread(file_contents, sizeof(char), st.st_size, f);
	fclose(f);
	
	file_contents[st.st_size+1] = '\0';
	return 0;
}

int main(int argc, char **argv) {
	if(load_file(
		(argc > 1) ? argv[1] : FILENAME
	) != 0) return 1;
	
	loop_beginnings = calloc(120, sizeof(char *));
		
	for(char *i = file_contents; *i; i++) {
		//putchar(*i);
		switch(*i) {
			case '+':
				(*ptr)++;
				break;
				
			case '-':
				(*ptr)--;
				break;
				
			case '.':
				putchar(*ptr);
				break;
				
			case ',':
				*ptr = getchar();
				break;
				
			case '>':
				ptr++;
				if(ptr > MEMORY + sizeof(MEMORY)) fputs("Went too far right\n", stdout);
				break;
				
			case '<':
				ptr--;
				if(ptr < MEMORY) fputs("Went too far left\n", stdout);
				break;
				
			case '[':
				loop_beginnings++;
				*loop_beginnings = i;
				break;
				
			case ']':
				if(*loop_beginnings == NULL) {
					fputs("Mismatched brackets... Nice one, dipshit\n", stdout);
					return 0;
				}
				
				if(*ptr != '\0') {
					i = *loop_beginnings;
				} else {
					loop_beginnings--;
				}
				break;
		}
	}
	
	free(file_contents);
	free(loop_beginnings);
	
	return 0;
}