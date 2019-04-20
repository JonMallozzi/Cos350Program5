#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

int main(){

int i = 0;

//printf("job id: %d\n", getpid());

if (fork() == 0){

printf("started string in background with the job id: %d\n", getpid());

execvp("./count",NULL);

}

return 0;
}
