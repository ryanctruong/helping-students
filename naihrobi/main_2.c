/***************************************************************

 ***************************************************************/

#include "naihrobi/general_1.h"


int main(void)
{
  
  int pipe1[2];
  int pipe2[2];
  // chaing the pipe to threads
  pthread_t thread1[2], thread2[2], thread3[2];//the threads for each chilld 
  char *letter="thread";
  int ret1, ret2, ret3;// this is the data for tyhe threads
  
  int status;//for wait()
  
  if(pipe(pipe1)<0)
    {
      fprintf(stderr, "Error opening thread #1\n\n");
      exit(100);
    }
 
  ret1=pthread_create(&thread1, NULL, thread_1, (void *)letter);//create a thread and call thread 1 process
    
      close(pipe1[0]);//close the read end of the pipe shared with child 2
      child1(0, pipe1[1]);
    
 
  close(pipe1[1]);//parent closes write end of pipe 1. Keep read end open, child 2 will need it
  
  if(pipe(pipe2)<0)
    { 
      close(thread1[0]);//close the remaining pipe1 end since we must exit now
      fprintf(stderr, "Error opening pipe #2\n\n");
      exit(100);
    }
  
  ret2=pthread_create(&thread2, NULL, thread_2, (void *)letter);//create a thread and call thread 2 process
    
      close(pipe2[0]);//close the read end of the pipe shared with child 3
      child2(pipe1[0], pipe2[1]);
    
  
  close(pipe1[0]);//parent closes read end of pipe 1
  
  close(pipe2[1]);//parent closes write end of pipe 2. Keep read end of pipe 2 open, child 3 will need it
  
  ret3=pthread_create(&thread3, NULL, thread_2, (void*)letter);//creat a thread and call thread 3 process
    child3(pipe2[0], 1);
  
  close(pipe2[0]);//parent closes read end of pipe 2. Parent has now closed all ends of both pipes

  /*wait for all three children in whatever order they complete*/
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
    
  return(0);
}
