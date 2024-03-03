#include "general.h"
#include <pthread.h>

typedef struct {
    int in;
    int out;
} pipe_args;

void* thread_child1(void* args) {
    pipe_args* pargs = (pipe_args*)args;
    child1(args);
    pthread_exit(NULL);
}

void* thread_child2(void* args) {
    pipe_args* pargs = (pipe_args*)args;
    child2(args);
    pthread_exit(NULL);
}

void* thread_child3(void* args) {
    pipe_args* pargs = (pipe_args*)args;
    child3(args);
    pthread_exit(NULL);
}

int main(void) {
    int pipe1[2]; 
    int pipe2[2]; 
    pthread_t t1, t2, t3; 
    pipe_args args1, args2, args3;

    if (pipe(pipe1) < 0 || pipe(pipe2) < 0) {
        fprintf(stderr, "Error opening pipes\n\n");
        exit(100);
    }

    args1.in = 0;
    args1.out = pipe1[1];
    pthread_create(&t1, NULL, thread_child1, &args1);

    args2.in = pipe1[0];
    args2.out = pipe2[1];
    pthread_create(&t2, NULL, thread_child2, &args2);

    args3.in = pipe2[0];
    args3.out = 1;
    pthread_create(&t3, NULL, thread_child3, &args3);

    close(pipe1[1]);
    close(pipe2[1]);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    
    close(pipe1[0]);
    close(pipe2[0]);

    return 0;
}
