#ifndef RENDERER_H
#define RENDERER_H

#include "Player.h"
#include "Map.h"
#include <Windows.h>

class Renderer {
private:
    int screenWidth, screenHeight;
    wchar_t* screen;
    HANDLE hConsole;
    DWORD dwBytesWritten;

public:
    Renderer(int width, int height);
    ~Renderer();

    void ClearScreen();
    void DrawMap(const Map& map);
    void DrawPlayer(const Player& player);
    void RenderFrame(float fDeltaTime, const Player& player, const Map& map);
};

#endif // RENDERER_H
