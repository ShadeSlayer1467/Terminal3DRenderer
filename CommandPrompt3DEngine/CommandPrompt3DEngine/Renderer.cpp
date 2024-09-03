#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>

#include "Player.h"
#include "Map.h"
#include "Renderer.h"
#include "Constants.h"

Renderer::Renderer(int width, int height)
    : screenWidth(width), screenHeight(height), dwBytesWritten(0) {
    screen = new wchar_t[screenWidth * screenHeight];
    hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
}

Renderer::~Renderer() {
    delete[] screen;
}

void Renderer::ClearScreen() {
    std::fill_n(screen, screenWidth * screenHeight, L' ');
}

void Renderer::DrawMap(const Map& map) {
    for (int nx = 0; nx < map.width; nx++) {
        for (int ny = 0; ny < map.height; ny++) {
            screen[(ny + 1) * screenWidth + nx] = map.data[ny * map.width + nx];
        }
    }
}

void Renderer::DrawPlayer(const Player& player) {
    screen[((int)player.y + 1) * screenWidth + (int)player.x] = 'P';
}

void Renderer::RenderFrame(float fDeltaTime, const Player& player, const Map& map) {
    ClearScreen();
    for (int x = 0; x < screenWidth; x++) {
        float fRayAngle = (player.angle - fFOV / 2) + ((float)x / (float)screenWidth) * fFOV;
        float fDistanceToWall = 0.0f;
        bool bHitWall = false;
        bool bHitBoundary = false;
        float fEyeX = cosf(fRayAngle);
        float fEyeY = sinf(fRayAngle);

        while (!bHitWall && fDistanceToWall < fDepth) {
            fDistanceToWall += 0.1f;
            int nTestX = (int)(player.x + fEyeX * fDistanceToWall);
            int nTestY = (int)(player.y + fEyeY * fDistanceToWall);

            if (map.OutOfBounds(nTestX, nTestY)) 
            {
                bHitWall = true;
                fDistanceToWall = fDepth;
            }
            else
            {
                if (map.IsWall(nTestX,nTestY))
                {
                    bHitWall = true;

                    std::vector<std::pair<float, float>> p; // distance, cross product magnitude

                    for (int tx = 0; tx < 2; tx++)
                    {
                        for (int ty = 0; ty < 2; ty++)
                        {
                            float vy = (float)nTestY + ty - player.y;
                            float vx = (float)nTestX + tx - player.x;
                            float d = sqrt(vx * vx + vy * vy);

                            // Calculate cross product magnitude
                            float cross = fabs(fEyeX * vy - fEyeY * vx);
                            p.push_back(std::make_pair(d, cross));
                        }
                    }

                    // Sort pairs by distance
                    std::sort(p.begin(), p.end(), [](const std::pair<float, float>& left, const std::pair<float, float>& right) {
                        return left.first < right.first;
                        });

                    // Check if the closest edge has a small cross product, indicating it's a boundary
                    float fBoundaryThreshold = 0.025f; // Tolerance value for boundary detection
                    if (p.at(0).second < fBoundaryThreshold || p.at(1).second < fBoundaryThreshold)
                    {
                        bHitBoundary = true;
                    }

                }
            }
        }

        int nCeiling = (float)(screenHeight / 2.0f) - screenHeight / ((float)fDistanceToWall);
        int nFloor = screenHeight - nCeiling;

        short nShade = ' ';
        nShade = (fDistanceToWall < fDepth / 4.0f) ? 0x2588 :
            (fDistanceToWall < fDepth / 3.0f) ? 0x2593 :
            (fDistanceToWall < fDepth / 2.0f) ? 0x2592 :
            (fDistanceToWall < fDepth) ? 0x2591 : ' ';
        if (bHitBoundary) nShade = '|';

        for (int y = 0; y < screenHeight; y++) {
            if (y <= nCeiling)
                screen[y * screenWidth + x] = ' ';
            else if (y > nCeiling && y <= nFloor)
                screen[y * screenWidth + x] = nShade;
            else {
                float b = 1.0f - (((float)y - screenHeight / 2.0f) / ((float)screenHeight / 2.0f));
                if (b < 0.25) nShade = '#';
                else if (b < 0.50) nShade = 'x';
                else if (b < 0.75) nShade = '.';
                else if (b < 0.90) nShade = '-';
                else nShade = ' ';
                screen[y * screenWidth + x] = nShade;
            }
        }
    }

    DrawMap(map);
    DrawPlayer(player);

    swprintf_s(screen, 50, L"X=%5.2f, Y=%5.2f, A=%3.2d, FPS=%5.2f", player.x, player.y, ((int)(player.angle * 180 / fPi) + 90) % 360, 1.0f / fDeltaTime);

    screen[screenWidth * screenHeight - 1] = '\0';
    WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, { 0, 0 }, &dwBytesWritten);
}
