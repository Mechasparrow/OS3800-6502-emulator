#include <iostream>

#include "program_loader/6502_loader.h"

int main(){
    Loader6502 loader {"../test_assembly/test.s19"};

    loader.readFileContents();
    
    return 0;
}