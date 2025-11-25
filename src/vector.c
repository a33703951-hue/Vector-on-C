#include <stdlib.h>
#include <string.h>

typedef struct{
    void* __data;
    int __size;
    int __pos;
    int __ellsize;
} Vector;

#define __VECTOR_DEFAULT_CAPACITY 5
#define __STRING_DEFAULT_CAPACITY 10

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
    free(v);
}


typedef struct string{
    char* __data;
    int __size;
    int __curr;
} string;

__declspec(dllexport) string* CreateString(){
    string* obj=(string*)malloc(sizeof(string));
    obj->__data=(char*)malloc(__STRING_DEFAULT_CAPACITY);
    obj->__size=__STRING_DEFAULT_CAPACITY;
    obj->__curr=0;
    obj->__data[obj->__curr]='\0';
    return obj;
}

__declspec(dllexport) const char* String_cstr(string* obj){
    return obj->__data;
}

__declspec(dllexport) void String_Free(string* obj){
    free(obj->__data);
    free(obj);
}

__declspec(dllexport) void __String_resize(string* s,int size){
    char* data=(char*)malloc(size);
    memcpy(data,s->__data,s->__curr);
    free(s->__data);
    s->__data=data;
    s->__size=size;
}

__declspec(dllexport) void String_addc(string* obj,const char* s){
    if (obj->__curr+strlen(s)+1<obj->__size)
        __String_resize(obj,obj->__size+(strlen(s)*2));
    memcpy(obj->__data+obj->__curr,s,strlen(s));
    obj->__curr+=strlen(s);
    obj->__data[obj->__curr] = '\0';
}

__declspec(dllexport) void String_adds(string* obj,string* other){
    if (obj->__curr+other->__curr+1<obj->__size)
        __String_resize(obj,other->__size*2);
    memcpy(obj->__data+obj->__curr,other->__data,other->__curr);
    obj->__curr+=other->__curr;
    obj->__data[obj->__curr] = '\0';
}

int String_size(string* o){
    return o->__curr;
}
