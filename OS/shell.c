#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int signo){
	printf("\n[SHELL ]");
	fflush(stdout);
}	

int main(int argc, char* argv[], char* envp[]){
	signal(SIGINT, handle_signal);
	char c = '\0';
	printf("\n[SHELL ]");
	while(c!=EOF){
		c = getchar();
		if(c=='\n') printf("[SHELL ]");
	}
	printf("\n");
	return 0;
}