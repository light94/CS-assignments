#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

int main(){
	int i, n, status;
	int f1=1,f2=1;
	scanf("%d",&n);

	for(i=0;i<n;++i){
		int pid = fork();
		if(pid==0){
			// child
			int f3 = f1 + f2;
			printf("%d\n",f3);
			f1 = f2;
			f2 = f3;
			exit(0);
		}else{
			// parent
			printf("Parent scheduled.. \n");
			waitpid(pid, &status, 0);
			int f3 = f1 + f2;
			f1 = f2;
			f2 = f3;
		}
	}
}