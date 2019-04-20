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
    
      //checks for a change directory call
      if (strcmp(arglist[0],"cd") == 0){
        printf("hi");

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

     }else{
      result = execute(arglist);
     }


      printf("result: %d\n", result);

      //exits when exits is given with no value using
      //512 because its the default with exit(2)
      if (result == 512){
            printf("exiting the shell");
            exit(1);
      }

      //returns with value given as argument for exit
      if(result != 0 && result != 256 && result != 512 && result !=-1){
        printf("exiting the shell with the exit value: %d \n",result);
        exit(result);
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

