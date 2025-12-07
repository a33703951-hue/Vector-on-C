#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef char*(*StrFunc)(void*);
typedef void*(*AddFunc)(const void*,const void*);
typedef void*(*SubFunc)(const void*,const void*);
typedef void*(*MulFunc)(const void*,const void*);
typedef void*(*DivFunc)(const void*,const void*);
typedef void*(*CopyFunc)(const void*);

typedef struct BasicObj{
    StrFunc str;
    AddFunc add;
    MulFunc mul;
    DivFunc di;
    SubFunc sub;
    CopyFunc copy;
} BasicObj;

typedef struct Int{
    BasicObj basic;
    int a;
} Int;

void Int_init(Int*);

char* Int_str(void* o){
    char* buf=malloc(15);
    Int a=*(Int*)o;
    sprintf(buf,"%d",a.a);
    return buf;
}

void* Int_add(const void* a,const void* b){
    Int* res=malloc(sizeof(Int));
    Int_init(res);
    res->a=((Int*)a)->a+((Int*)b)->a;
    return res;
}

void* Int_sub(const void* a,const void* b){
    Int* res=malloc(sizeof(Int));
    Int_init(res);
    res->a=((Int*)a)->a-((Int*)b)->a;
    return res;
}

void* Int_mul(const void* a,const void* b){
    Int* res=malloc(sizeof(Int));
    Int_init(res);
    res->a=((Int*)a)->a*((Int*)b)->a;
    return res;
}

void* Int_div(const void* a,const void* b){
    Int* res=malloc(sizeof(Int));
    Int_init(res);
    res->a=((Int*)a)->a/((Int*)b)->a;
    return res;
}

void* Int_copy(const void* a){
    Int* res=malloc(sizeof(Int));
    Int_init(res);
    res->a=((Int*)a)->a;
    return res;
}

void Int_init(Int* a){
    a->basic.str=Int_str;
    a->basic.add=Int_add;
    a->basic.sub=Int_sub;
    a->basic.mul=Int_mul;
    a->basic.di=Int_div;
    a->basic.copy=Int_copy;
    a->a=0;
}

typedef struct Var{
    BasicObj* var;
} Var;

void Var_set(Var* obj,BasicObj* o){
    obj->var=o;
}

char* Var_str(Var* o){
    return o->var->str(o->var);
}

Var Var_add(Var* a,Var* b){
    Var k;
    BasicObj* r=a->var->add(a->var,b->var);
    Var_set(&k,r);
    return k;
}

Var Var_sub(Var* a,Var* b){
    Var k;
    BasicObj* r=a->var->sub(a->var,b->var);
    Var_set(&k,r);
    return k;
}

Var Var_mul(Var* a,Var* b){
    Var k;
    BasicObj* r=a->var->mul(a->var,b->var);
    Var_set(&k,r);
    return k;
}

Var Var_div(Var* a,Var* b){
    Var k;
    BasicObj* r=a->var->di(a->var,b->var);
    Var_set(&k,r);
    return k;
}

Var Var_copy(Var* a){
    Var k;
    BasicObj* r=a->var->copy(a->var);
    Var_set(&k,r);
    return k;
}

int main() {
    Int* a=malloc(sizeof(Int));
    Int_init(a);
    a->a=88;
    Var g;
    Var_set(&g,(BasicObj*)a);
    Var h=Var_copy(&g);
    printf("%s",Var_str(&h));
    return 0;
}
