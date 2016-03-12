#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[], char* envp[]){
	char c = '\0';
	printf("\n[SHELL ]");
	while(c!=EOF){
		c = getchar();
		if(c=='\n') printf("[SHELL ]");
	}
	printf("\n");
	return 0;
}