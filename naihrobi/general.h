/***************************************************************
 

 ***************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

int child1(int in, int out);
int child2(int in, int out);
int child3(int in, int out);
int myGetline(int in, char *buf);
bool isAllLeft(char *s);
bool isAllRight(char *s);
void replaceNewline(char *buf);
