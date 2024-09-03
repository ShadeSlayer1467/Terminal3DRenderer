#ifndef MAP_H
#define MAP_H

#include <string>

class Map {
public:
    int width, height;
    std::wstring data;

    Map(int w, int h, const std::wstring& mapData);

    bool OutOfBounds(int x, int y) const;
    bool IsWall(int x, int y) const;
};

#endif // MAP_H
