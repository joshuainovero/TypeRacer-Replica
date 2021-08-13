#include "typeracer.h"

int main() {
    srand(time(NULL));
    DEBUG_LOG("Debug mode\n")
    TypeRacer typeracer;
    typeracer.run();
    return 0;
}