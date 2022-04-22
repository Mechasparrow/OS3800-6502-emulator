#include <iostream>
#include <fstream>

bool validFile(std::string fileName);
bool getInputFiles(int argc, char ** argv, std::string * assemblyfile, std::string * addressesToCheckFile);