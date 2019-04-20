/* execute.c - code used by small shell to execute commands */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>



int execute(char *argv[])
/*
 * purpose: run a program passing it arguments
 * returns: status returned via wait, or -1 on error
 *  errors: -1 on fork() or wait() errors
 */
{
  int	pid ;
  int	child_info = -1;

  if ( argv[0] == NULL )		/* nothing succeeds	*/
    return 0;

  if ( (pid = fork())  == -1 )
    perror("fork");
  else if ( pid == 0 ){
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);

    if(strcmp(argv[0],"exit") == 0){
      if(argv[1] != NULL){
       
       //checks to see if exit of 1 or 0
       //asks for a different value because those are used 
       //for exiting when an command has an error or is successful
       if(atoi(argv[1]) == 256 || atoi(argv[1]) == 0){
        printf("please give an exit value besides the default of 0 or 256");
        exit(1);
        }

      exit(atoi(argv[1]));
      
      //default exit
      }else{
      exit(2);
      }
     
    //if statement for background commands
    //be seeing if the end of argv is &
    }/*else if (strcmp(strchr(*argv,'&'),"c&") == 0){
      printf("testing %d",strcmp(strchr(*argv,'&'),"&"));
      exit(0);

    
    //else normal exacution of commands  
    }*/else{
    execvp(argv[0], argv);
    perror("cannot execute command");
    exit(1);

    }

  }
  else {
    if ( wait(&child_info) == -1 )
      perror("wait");
  }
  return child_info;
}
