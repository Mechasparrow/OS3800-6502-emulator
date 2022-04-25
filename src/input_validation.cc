#include "input_validation.h"

bool getInputFiles(int argc, char ** argv, std::string * assemblyfile, std::string * addressesToCheckFile){
    std::string assemblyFilePath;
    std::string addressesToCheckFilePath;
    bool goodToRun = false;

    if (argc <= 1){
        goodToRun = false;
    }else if (argc == 2){
        assemblyFilePath = std::string(argv[1]);
        bool assemblyFileExists = validFile(assemblyFilePath);

        if (assemblyFileExists){
            goodToRun = true;
            *assemblyfile = assemblyFilePath;
        }else{
            goodToRun = false;
        }

    }else if (argc >= 3){
        assemblyFilePath = std::string(argv[1]);
        addressesToCheckFilePath = std::string(argv[2]);

        bool assemblyFileExists = validFile(assemblyFilePath);
        bool addressesToCheckFileExists = validFile(assemblyFilePath);

        if (assemblyFileExists && addressesToCheckFileExists){
            goodToRun = true;
            *assemblyfile = assemblyFilePath;
            *addressesToCheckFile = addressesToCheckFilePath;
        }else{
            goodToRun = false;
        }
    }
    
    return goodToRun;    
}

bool validFile(std::string fileName){
    std::ifstream file;
    file.open(fileName);

    if (file){
        file.close();
        return true;
    }else{
        return false;
    }
}