#include "Engine.h"
#include "GameScenes.h"

Engine mainEngine;

Menu menu;

int main()
{ 
    mainEngine.LoadScene(menu);
    mainEngine.Run();
    return 0;
}