#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>


int main(){

    char userNameBuf[50];
    int userName = getlogin_r(userNameBuf,sizeof(userNameBuf));


    char *cat = "cat";
    char **catPointer = &cat;

    

    printf("t: %c\n", cat[strlen(cat) -2]);
    printf("tagain: %c\n", cat[2]);

    printf("**buffer end: %c\n", *catPointer[strlen(cat) -1]);

    //if(strcmp())

    size_t currBuffSize = strlen(userNameBuf);

    printf("size of the buff: %ld \n", currBuffSize);

    userNameBuf[currBuffSize++] = ' ';

    printf("%s\n",userNameBuf);
  
   //gets the current working directory and puts in on the prompt
   char currWorkingDir[30];
   getcwd(currWorkingDir,sizeof(currWorkingDir));

   strcat(userNameBuf,currWorkingDir);

   printf("%s \n",userNameBuf);


currBuffSize = strlen(userNameBuf);
   userNameBuf[currBuffSize++] = '>';

   printf("size of buff after directory: %ld\n",strlen(userNameBuf));

   printf("%s \n",userNameBuf);
    return 0;
}