#include "typeracer.h"
long long getFileSize()
{
    std::streampos fsize = 0;

    std::ifstream myfile("myfuckingdata.json", std::ios::in);  // File is of type const char*

    fsize = myfile.tellg();         // The file pointer is currently at the beginning
    myfile.seekg(0, std::ios::end);      // Place the file pointer at the end of file

    fsize = myfile.tellg() - fsize;
    myfile.close();

    static_assert(sizeof(fsize) >= sizeof(long long), "Oops.");

    std::cout << "size is: " << fsize << " bytes.\n";
    return fsize;
}

int main() {
    //std::cout << getFileSize() << std::endl;
    srand(time(NULL));
    DEBUG_LOG("Debug mode\n")
    TypeRacer typeracer;
    typeracer.run();
    return 0;
}