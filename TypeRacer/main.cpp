#include "typeracer.h"
#ifdef _DEBUG
#define ENGINE int main()
#else
#define ENGINE int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance,LPSTR lpszArgument, int nCmdShow)
#endif

ENGINE{
    srand(time(NULL));
    DEBUG_LOG("Debug mode\n")
    TypeRacer typeracer;
    typeracer.run();
    return 0;
}