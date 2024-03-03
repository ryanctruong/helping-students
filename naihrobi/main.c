/***************************************************************

 ***************************************************************/

#include "general.h"

int main(void)
{
  int pipe1[2];//pipe for child 1 and child 2 to share
  int pipe2[2];//pipe for child 2 and child 3 to share
  int status;//for wait()
  
  if(pipe(pipe1)<0)
    {
      fprintf(stderr, "Error opening pipe #1\n\n");
      exit(100);
    }
 
  if(fork() == 0)//Fork and call child 1 process
    {
      close(pipe1[0]);//close the read end of the pipe shared with child 2
      child1(0, pipe1[1]);
    }
 
  close(pipe1[1]);//parent closes write end of pipe 1. Keep read end open, child 2 will need it
  
  if(pipe(pipe2)<0)
    { 
      close(pipe1[0]);//close the remaining pipe1 end since we must exit now
      fprintf(stderr, "Error opening pipe #2\n\n");
      exit(100);
    }
  
  if(fork() == 0)//Fork and call child 2 process
    {   
      close(pipe2[0]);//close the read end of the pipe shared with child 3
      child2(pipe1[0], pipe2[1]);
    }
  
  close(pipe1[0]);//parent closes read end of pipe 1
  
  close(pipe2[1]);//parent closes write end of pipe 2. Keep read end of pipe 2 open, child 3 will need it
  
  if(fork() == 0)//Fork and call child 3 process
    child3(pipe2[0], 1);
  
  close(pipe2[0]);//parent closes read end of pipe 2. Parent has now closed all ends of both pipes

  /*wait for all three children in whatever order they complete*/
  wait(&status);
  wait(&status);
  wait(&status);
    
  return(0);
}
