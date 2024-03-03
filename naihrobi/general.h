#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include <pthread.h> 
void* child1(void* args);
void* child2(void* args);
void* child3(void* args);
int myGetline(int in, char *buf);
bool isAllLeft(char *s);
bool isAllRight(char *s);
void replaceNewline(char *buf);
