#include <string>
#include "Map.h"

Map::Map(int w, int h, const std::wstring& mapData)
    : width(w), height(h), data(mapData) {}

bool Map::OutOfBounds(int x, int y) const {
    return (x < 0 || x >= width || y < 0 || y >= height);
}
bool Map::IsWall(int x, int y) const {
    return data[y * width + x] == '#';
}
