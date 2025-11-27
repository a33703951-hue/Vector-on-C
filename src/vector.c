#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char __errbuf[1024];

const char* GetError(){
    return __errbuf;
}

typedef struct array{
    void* __data;
    int __ellsize;
    int __size;
} array;

__declspec(dllexport) array* CreateArray(int size,int ellsize){
    array* obj=(array*)malloc(sizeof(array));
    obj->__data=malloc(size*ellsize);
    obj->__ellsize=ellsize;
    obj->__size=size;
    return obj;
}

__declspec(dllexport) void* __Array_get(array* o,int index){
    if (index>o->__size){
        const char* mes="Out of range: array";
        memcpy(__errbuf,mes,strlen(mes)+1);
        return NULL;
    }
    return ((char*)(o->__data))+(o->__ellsize*index);
}

__declspec(dllexport) void Array_Free(array* o){
    free(o->__data);
    free(o);
}

__declspec(dllexport) int Array_size(array* obj){
    return obj->__size;
}

__declspec(dllexport) array* Array_copy(array* o){
    array* n=CreateArray(o->__size,o->__ellsize);
    memcpy(n->__data,o->__data,o->__size*o->__ellsize);
    return n;
}

typedef struct{
    void* __data;
    int __size;
    int __pos;
    int __ellsize;
} Vector;

#define __VECTOR_DEFAULT_CAPACITY 5
#define __STRING_DEFAULT_CAPACITY 10

__declspec(dllexport) void* __Vector_begin(Vector* v){
    return v->__data;
}

__declspec(dllexport) void* __Vector_end(Vector* v){
    return ((char*)(v->__data))+(v->__pos*v->__ellsize);
}

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
    if (v->__pos==0){
        const char* mes="Already in the end cannot Pop back: Vector";
        memcpy(__errbuf,mes,strlen(mes)+1);
        return;
    }
    v->__pos-=1;
}

__declspec(dllexport) int Vector_Size(Vector* v){
    return v->__pos;
}

__declspec(dllexport) int Vector_Capacity(Vector* v){
    return v->__size;
}

__declspec(dllexport) int __Vector_ellsize(Vector* v){
    return v->__ellsize;
}

__declspec(dllexport) void* Vector_Get(Vector* v,int index){
    if (index>=v->__pos || index<0){
        const char* mes="Out of range: Vector";
        memcpy(__errbuf,mes,strlen(mes)+1);
        return NULL;
    }
    char* ptr=(char*)v->__data;
    void* a=(void*)(ptr+index*v->__ellsize);
    return a;
}

__declspec(dllexport) Vector* Vector_Copy(Vector* v){
    Vector* n=CreateVector(v->__ellsize);
    Vector_Resize(n,v->__size);
    memcpy(n->__data,v->__data,v->__pos*v->__ellsize);
    return n;
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
    obj->__data[obj->__curr]='\0';
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

__declspec(dllexport) string* String_addc(string* obj,const char* s){
    if (obj->__curr+strlen(s)+1>obj->__size)
        __String_resize(obj,obj->__size+(strlen(s)*2));
    memcpy(obj->__data+obj->__curr,s,strlen(s));
    obj->__curr+=strlen(s);
    obj->__data[obj->__curr] = '\0';
    return obj;
}

__declspec(dllexport) string* String_adds(string* obj,string* other){
    if (obj->__curr+other->__curr+1>obj->__size)
        __String_resize(obj,other->__size*2);
    memcpy(obj->__data+obj->__curr,other->__data,other->__curr);
    obj->__curr+=other->__curr;
    obj->__data[obj->__curr] = '\0';
    return obj;
}

__declspec(dllexport) string* String_Copy(string* o){
    string* n=CreateString();
    String_adds(n,o);
    return n;
}

__declspec(dllexport) int String_size(string* o){
    return o->__curr;
}

__declspec(dllexport) void String_set(string* o,const char* s){
    memcpy(o->__data,s,strlen(s));
    o->__curr=strlen(s);
}

#define BINARY 1<<1
#define RP 1<<2
#define APPEND 1<<3

typedef struct file{
    FILE* f;
} file;

typedef struct Ifile{
    file f;
} Ifile;

__declspec(dllexport) Ifile* CreateIfile(const char* name,int flags){
    Ifile* n=(Ifile*)malloc(sizeof(Ifile));
    string* mode=CreateString();
    String_addc(mode,"r");
    if ((flags & BINARY)!=0)
        String_addc(mode,"b");
    else if ((flags & RP)!=0)
        String_addc(mode,"+");
    n->f.f=fopen(name,String_cstr(mode));
    String_Free(mode);
    return n;
}

__declspec(dllexport) void Ifile_read(Ifile* file,int bytes,void* dst){
    fread(dst,1,bytes,file->f.f);
}

__declspec(dllexport) void File_close(file* file){
    fclose(file->f);
    free(file);
}

typedef struct Ofile{
    file f;
} Ofile;

__declspec(dllexport) Ofile* CreateOfile(const char* name,int flags){
    Ofile* n=(Ofile*)malloc(sizeof(Ofile));
    string* mode=CreateString();
    if ((flags & APPEND)!=0)
        String_addc(mode,"a");
    else    
        String_addc(mode,"w");
    if ((flags & BINARY)!=0){
        String_addc(mode,"b");
    }
    n->f.f=fopen(name,String_cstr(mode));
    String_Free(mode);
    return n;
}

__declspec(dllexport) void Ofile_write(Ofile* file,int bytes,const void* data){
    fwrite(data,1,bytes,file->f.f);
}
