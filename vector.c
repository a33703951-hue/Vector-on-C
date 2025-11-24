#include <cstdlib>
#include <cstring>

typedef struct{
    void* __data;
    int __size;
    int __pos;
    int __ellsize;
} Vector;

#define __VECTOR_DEFAULT_CAPACITY 5

__declspec(dllexport) Vector* CreateVector(int ellement_size){
    Vector* v=(Vector*)malloc(sizeof(Vector));
    v->__ellsize=ellement_size;
    v->__pos=0;
    v->__size=__VECTOR_DEFAULT_CAPACITY;
    v->__data=malloc(v->__size*v->__ellsize);
    return v;
}

__declspec(dllexport) void Vector_Resize(Vector* v,int newsize){
    void* n=malloc(v->__ellsize*newsize);
    memcpy(n,v->__data,v->__pos*v->__ellsize);
    free(v->__data);
    v->__data=n;
    v->__size=newsize;
    
}

__declspec(dllexport) void Vector_PushBack(Vector* v,const void* ell){
    char* ptr=(char*)v->__data;
    if (v->__pos>=v->__size)
        Vector_Resize(v,v->__size*2);
    memcpy(ptr+v->__pos*v->__ellsize,ell,v->__ellsize);
    v->__pos+=1;
}

__declspec(dllexport) void Vector_PopBack(Vector* v){
    if (v->__pos==0)
        return;
    v->__pos-=1;
}

__declspec(dllexport) int Vector_Size(Vector* v){
    return v->__pos;
}

__declspec(dllexport) int Vector_Capacity(Vector* v){
    return v->__size;
}

__declspec(dllexport) void* Vector_Get(Vector* v,int index){
    if (index>=v->__pos || index<0)
        return NULL;
    char* ptr=(char*)v->__data;
    void* a=(void*)(ptr+index*v->__ellsize);
    return a;
}

__declspec(dllexport) void Vector_Free(Vector *v){
    free(v->__data);
}
