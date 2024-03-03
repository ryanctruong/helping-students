/***************************************************************
 

 ***************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include<pthread.h>

void *thread_1(void *ptr);
void *thread_2(void *ptr);
void *thread_3(void *ptr);
int myGetline(int in, char *buf);
bool isAllLeft(char *s);
bool isAllRight(char *s);
void replaceNewline(char *buf);
