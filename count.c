#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

int main(){

//printf("job id: %d\n", getpid());

for(int i = 0; i < 3; i++){
printf("%d\n",i);
fflush(stdin);
usleep(2000000);
}


return 0;
}
