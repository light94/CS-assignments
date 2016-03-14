#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define FILE_SIZE 1000
#define BUF_SIZE  100
#define PARAM_SIZE  10 // number of parameters

char prompt[BUF_SIZE];
char *params[PARAM_SIZE];

void setPrompt(){
	strcat(prompt, "> ");
}

int _chdir(){
	int st = chdir(params[1]);
	if(st==0) {
		getcwd(prompt, 100);
		setPrompt();
	}else{
		perror(params[1]);
	}
}

int _pwd(){
	char cwd[100];
	getcwd(cwd,100);
	printf("%s\n", cwd);
}

int _mkdir(){
	int st = mkdir(params[1], S_IRWXU);
	if(st!=0)
		perror('\0');
}

int _rmdir(){
	int st = rmdir(params[1]);
	if(st!=0){
		perror(params[1]);
		//if(errno==ENOENT)
	}
}

int execute(int param_no){
	if(strcmp(params[0], "cd")==0){
		return _chdir();
	}else if(strcmp(params[0], "pwd")==0){
		return _pwd();
	}else if(strcmp(params[0], "mkdir")==0){
		return _mkdir();
	}else if(strcmp(params[0], "rmdir")==0){
		return _rmdir();
	}else if(strcmp(params[0], "ls")==0){
		/*if(params[1]=='-l'){

		}*/
	}else if(strcmp(params[0], "cp")==0){
		// check existence and read permission
	
	}else if(strcmp(params[0], "exit")==0){

	}else{

	}
}



int parse(char *buf, int n){
	char *cmd = buf, *tok;
	int param_no = 0;
	tok = strtok(cmd, " ");
	while(tok!='\0'){
		params[param_no++] = tok;
		tok = strtok(NULL, " ");
	}
	return param_no;
}


int main(){
	getcwd(prompt, 100);
	setPrompt();
	printf("%s", prompt);
	char in = ' ';
	char buf[BUF_SIZE];
	memset(buf,'\0',BUF_SIZE);
	int index = 0;
	while(in != EOF){
		in = getchar();
		switch(in){
			case '\n':
				if(index==0)
					printf("%s", prompt);
				else{
					int param_no = parse(buf, BUF_SIZE);
					execute(param_no);
					memset(buf,'\0',BUF_SIZE);	
					index = 0;
					printf("%s", prompt);
				}
						
				break;
			default:
				buf[index++] = in;
				break;
		}
	}
	
}