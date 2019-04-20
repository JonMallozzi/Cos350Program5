/*******************************************************
* Group: Jonathan Gilikson, Jon Mallozzi, Fazil Shaikh *
* COS 350 Project 5                                    *
* Project 5: mysh                                      *
* Date: 4/19/19                                        *
*******************************************************/

/**  smsh1.c  small-shell version 1
 **		first really useful version after prompting shell
 **		this one parses the command line into strings
 **		uses fork, exec, wait, and ignores signals
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include "smsh.h"

//not used anymore
//as it was changed
#define	DFL_PROMPT	"> "

 

int main(){
  char	*cmdline, *prompt, **arglist;
  int	result;
  void	setup();

  //buffer used to change the prompt
  char promptBuf[20];

  //puts the username as first thing in buff
  getlogin_r(promptBuf,sizeof(promptBuf));

  //puts the :$  at the end of the prompt to finish it
  strcat(promptBuf,":$ ");

  prompt = promptBuf ;
  setup();

  while ( (cmdline = next_cmd(prompt, stdin)) != NULL ){
    if ( (arglist = splitline(cmdline)) != NULL  ){
    
      
      //checks to see if the shell should exit
      if(strcmp(arglist[0],"exit") == 0 ){
         
        //checks to see if the user gave input for the exit
        if(arglist[1] != NULL){
         
          //exits with the value given by user input
          printf("exiting the shell with the exit value: %d \n",atoi(arglist[1]));
          exit(atoi(arglist[1]));
        
        //exits normally
        }else{
           
           printf("exiting the shell\n");
           exit(0);
        }

      //checks for a change directory call
      }else if (strcmp(arglist[0],"cd") == 0){

        //checks if the directory can be changed to
        if(chdir(arglist[1]) == -1){
        perror("cannot change directory");

        //changes to home if just cd is given  
        }else if (arglist[1] == NULL){
       
        chdir(getenv("HOME"));

        //changes to directory given as an argument  
        }else{
        chdir(arglist[1]);
        }
    
      //checks to run a process in the background
     }else if((cmdline[strlen(cmdline) - 1]) == '&'){

       //removes the & from the end
       cmdline[strlen(cmdline) - 1] = '\0';

      //forking for the background process
      if(fork() == -1){

        //returns an error if forking caused an error
        perror("fork error");

     //just does normal commands if no new commands are found
      }else{
        
        //gets and stores the background's processes pid
        pid_t backgroundPid = getpid();
        
        //status of the background task
        int stat;

        printf("started %s in background with the job id: %d\n",arglist[0],backgroundPid);

        //running arglist[0]
        execvp(arglist[0], arglist);
        perror("cannot execute command");

       
       waitpid(backgroundPid,&stat,0);
       
       //checking to see what waitpid returned
       if(WIFEXITED(stat))
         printf("Background task %d terminated with the status: %d\n",
                                                   backgroundPid,WIFEXITED(stat));

      }
      
      }else{
      result = execute(arglist);
     }
      freelist(arglist);
    }
    free(cmdline);
  }
  return 0;
}

void setup()
/*
 * purpose: initialize shell
 * returns: nothing. calls fatal() if trouble
 */
{
  signal(SIGINT,  SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n)
{
  fprintf(stderr,"Error: %s,%s\n", s1, s2);
  exit(n);
}

