// CommandPrompt3DEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

#include <Windows.h>
#include "Renderer.h"
#include "Player.h"
#include "Map.h"
#include "Constants.h"

int GameLoop()
{
    // Initialize classes
    Renderer renderer(nScreenWidth, nScreenHeight);
    Player player(fPlayerX, fPlayerY, fPlayerA);
    Map map(nMapWidth, nMapHeight,
        L"#.......################################"
        L"#..................##..................#"
        L"#.....#........######.....##############"
        L"#.....#............##.....#............#"
        L"#.....#............##.....#............#"
        L"#..####............##..####............#"
        L"#...........#########...........########"
        L"#..................##..................#"
        L"#..................######..............#"
        L"#......................................#"
        L"#...#######............#######.........#"
        L"#..................##..................#"
        L"#..................##..................#"
        L"#..................##..................#"
        L"#...#####..........##...#####..........#"
        L"#......#...........##......#...........#"
        L"#......#.....####..##......#.....####..#"
        L"#..................##..................#"
        L"#..................##..................#"
        L"##############################..########"
        L"##############################..########"
        L"#..................##..................#"
        L"#.....#........######.....##############"
        L"#.....#............##.....#............#"
        L"#.....#............##.....#............#"
        L"#..####............##..####............#"
        L"#...........#########...........########"
        L"#..................##..................#"
        L"#..................######..............#"
        L"#......................................#"
        L"#...#######............#######.........#"
        L"#..................##..................#"
        L"#..................##..................#"
        L"#..................##..................#"
        L"#...#####..........##...#####..........#"
        L"#......#...........##......#...........#"
        L"#......#.....####..##......#.....####..#"
        L"#..................##..................#"
        L"#..................##..................#"
        L"########################################");

    auto nTimePoint1 = std::chrono::system_clock::now();
    auto nTimePoint2 = nTimePoint1;
    int frameCount = 0;

    while (1)
    {
        nTimePoint2 = std::chrono::system_clock::now();
        std::chrono::duration<float> chronoDeltaTime = nTimePoint2 - nTimePoint1;
        nTimePoint1 = nTimePoint2;
        float fDeltaTime = chronoDeltaTime.count();

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            break;

        // Handle player movement
        if (GetAsyncKeyState((unsigned short)cRotateLeft) & 0x8000) player.Rotate(-fDeltaTime);
        if (GetAsyncKeyState((unsigned short)cRotateRight) & 0x8000) player.Rotate(fDeltaTime);

        float moveStep = player.speed * fDeltaTime;
        if (GetAsyncKeyState((unsigned short)cLeft) & 0x8000) player.Move(-cosf(player.angle + fPi / 2.0f) * moveStep, -sinf(player.angle + fPi / 2.0f) * moveStep);
        if (GetAsyncKeyState((unsigned short)cRight) & 0x8000) player.Move(cosf(player.angle + fPi / 2.0f) * moveStep, sinf(player.angle + fPi / 2.0f) * moveStep);
        if (GetAsyncKeyState((unsigned short)cForward) & 0x8000) player.Move(cosf(player.angle) * moveStep, sinf(player.angle) * moveStep);
        if (GetAsyncKeyState((unsigned short)cBackward) & 0x8000) player.Move(-cosf(player.angle) * moveStep, -sinf(player.angle) * moveStep);

        // Collision detection
        if (map.IsWall((int)player.x, (int)player.y)) {
            // Undo movement if collision detected
            if (GetAsyncKeyState((unsigned short)cLeft) & 0x8000) player.Move(cosf(player.angle + fPi / 2.0f) * moveStep, sinf(player.angle + fPi / 2.0f) * moveStep);
            if (GetAsyncKeyState((unsigned short)cRight) & 0x8000) player.Move(-cosf(player.angle + fPi / 2.0f) * moveStep, -sinf(player.angle + fPi / 2.0f) * moveStep);
            if (GetAsyncKeyState((unsigned short)cForward) & 0x8000) player.Move(-cosf(player.angle) * moveStep, -sinf(player.angle) * moveStep);
            if (GetAsyncKeyState((unsigned short)cBackward) & 0x8000) player.Move(cosf(player.angle) * moveStep, sinf(player.angle) * moveStep);
        }

        // Render the frame
        renderer.RenderFrame(fDeltaTime, player, map);

        frameCount++;
    }

    return frameCount;
}

int main()
{
    GameLoop();

    std::cin.clear();
    std::cin.ignore(32767, '\n');
    std::cin.get();
}
