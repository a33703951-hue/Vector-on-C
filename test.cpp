#include <iostream>
#include "vector.h"

int main(){
    Vector* vec=CreateVector(sizeof(int));
    int a=99,b=88,c=77;
    Vector_PushBack(vec,&a);
    Vector_PushBack(vec,&b);
    Vector_PushBack(vec,&c);
    Vector_erease(vec,1);
    std::cout<<VECTOR_GET(vec,2,int);
    return 0;
}