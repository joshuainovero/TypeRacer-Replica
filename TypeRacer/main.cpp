#include "typeracer.h"

int main() {
    srand(time(NULL));
    #ifdef _DEBUG
    std::cout << "debug mode" << std::endl;
    #endif
    TypeRacer typeracer;
    typeracer.run();
    return 0;
}