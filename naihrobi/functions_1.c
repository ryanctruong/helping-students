/***************************************************************

 ***************************************************************/

#include "naihrobi/general_1.h"

/***************************************************************
 thread 1
***************************************************************/
//int child1(int in, int out)
void *thread_1(void *ptr)
{
  int  len;
  char buf[16384];
  char *token;
  
  while ((len=myGetline(in, buf)) > 0)//read a line from the input FD
    {
      if(buf[0]=='\n')
	continue;
      replaceNewline(buf);//get rid of '\n' since we don't want it to show up in a string
      
      token=strtok(buf, " "); //get the first token
      write(out, token, strlen(token));//send this first token to the next child
      write(out, "\n", 1);//and send a '\n' so myGetline will work right
      
      while((token=strtok(0, " "))){//keep getting tokens from the input string
	write(out, token, strlen(token));//send this first token to the next child
	write(out, "\n", 1);//and send a '\n' so myGetline will work right
      }
    }
  close(out);//if we don't close, child 2 will never see EOF
  exit(0);
}

/***************************************************************
 thread 2
***************************************************************/
//int child2(int in, int out)
void *thread_2(void *ptr)
{
  int  len;
  char token[80];
  
  int fd;
  
  fd = open("left.out", O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);//prepare the output file
  
  if(!fd)
    {
      printf("Error opening file 'left.out'\n\n");
      exit(100);
    }  
  
  while ((len=myGetline(in, token)) > 0)//tokens will be coming one at a time in child 2
    {
      replaceNewline(token);
      
      if(isAllLeft(token))
	{
	  write(fd, token, strlen(token));//write to "allLeft" output file
	  write(fd, "\n", 1);
	}
      else
	{	  
	  write(out, token, strlen(token));//send to child 3
	  write(out, "\n", 1);
	}     
    }
  close(in);//close all file descriptors
  close(out);
  close(fd);
  exit(0);
}

/***************************************************************
 thread 3
***************************************************************/
//int child3(int in, int out)
void *thread_3(void *ptr)
{
  int len;
  char token[80];
  int fd;
  
  fd = open("right.out", O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);//set up other output file
  
  if(!fd)
    {
      printf("Error opening file 'right.out'\n\n");
      exit(100);
    }
  
  while ((len=myGetline(in, token)) > 0)//tokens are coming one at a time in child 3 also
    {   
      replaceNewline(token);
      
      if(isAllRight(token))
	{
	  write(fd, token, strlen(token));/*write to output file*/
	  write(fd, "\n", 1);
	}
      else
	{	 
	  write(out, token, strlen(token));/*write to standard output*/
	  write(out, "\n", 1);
	}                      
    }
  close(in);//close all FDs
  close(fd);
  exit(0);  
}

/***************************************************************
 The routine given by Dr. Westall to read one character at a time
 from a pipe, or any file descriptor for that matter.
***************************************************************/
int myGetline(int in, char *loc)
{
  int len = 0;
  
  while (read(in, loc, 1) > 0)
    {
      len += 1;
      
      if (*loc == '\n')
	break;         
      loc++;
    }
  return(len);
}

/***************************************************************

 ***************************************************************/
bool isAllLeft(char *s)
{
  int i;
  
  for(i=0;i<strlen(s);i++)
    {
      switch(tolower(s[i]))
	{
	case 'y':
	case 'h':
	case 'n':
	case 'u':
	case 'j':
	case 'm':
	case 'i':
	case 'k':
	case 'o':
	case 'l':
	case 'p':
	case '6':
	case '7':
	case '8':
	case '9':
	case '0':
	  return 0;
	}
    }
  return 1;
} 
/***************************************************************

 ***************************************************************/
bool isAllRight(char *s)
{
  int i;
  
  for(i=0;i<strlen(s);i++)
    {
      switch(tolower(s[i]))
	{
	case 'q':
	case 'a':
	case 'z':
	case 'w':
	case 's':
	case 'x':
	case 'e':
	case 'd':
	case 'c':
	case 'r':
	case 'f':
	case 'v':
	case 't':
	case 'g':
	case 'b':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	  return 0;
	}
    }
  return 1;
}


/***************************************************************
 I use this function to take out the newline character and replace
 it with the null character.
***************************************************************/
void replaceNewline(char *buf)
{
  int i=0;
  while(buf[i]!='\n')
    i++;
  
  buf[i]='\0';
}
