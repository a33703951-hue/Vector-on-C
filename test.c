#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "vec.c"

void* worker(void* o){
    sleep(3);
    int* res=malloc(sizeof(int));
    *res=(*(int*)o)*5;
    return res;
}

int main(){
    Thread* thread=CreateThread();
    int a=6;
    Thread_start(thread,worker,&a);
    int res=*(int*)Thread_join(thread);
    printf("%d",res);
}