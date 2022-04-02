#include <iostream>

#include "program_loader/6502_loader.h"

int main(){
    DataBus mainDataBus;
    Loader6502 loader {"../test_assembly/test.s19"};

    loader.readFileContents();
    
    if (loader.recordRead){
        loader.burnRecords(&mainDataBus);
    }

    //fetch

    //execute

    //increment PC

    //^ loop the 3 steps

    return 0;
}