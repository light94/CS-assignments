#include <stdio.h>
#include <wait.h>
#include <stdlib.h>

int getfib(n){
	int f1 = 1, f2 = 1,f3 = 1,i;
	if (n == 1 || n == 2)
		return 1;
	for(i = 3; i <= n; ++i){
		f3 = f1 + f2;
		f1 = f2;
		f2 = f3;
	}
	return f3;
}

int main(){
	int status, i, n;
	scanf("%d", &n);
	int ar[n], pid[n];
	for(i=0;i<n;++i){
		pid[i] = fork();
		if(pid[i]==0){
			exit(getfib(i+1));
		}
	}

	for(i=0;i<n;++i){
		// wait for all child processes 
		waitpid(pid[i], &status, 0);
		ar[i] = status>>8;
	}
	for(i=0;i<n;++i) printf("%d ",ar[i]);
	printf("\n");
	return 0;
}