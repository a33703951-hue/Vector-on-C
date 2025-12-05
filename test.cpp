#include <iostream>
#include "vector.h"

int main(){
    State s=CreateState();
    State_set(s,"shitted",1);
    std::cout<<State_isOn(s,"shitted");
    return 0;
}