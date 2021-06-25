#include "map.h"

Map::Map()
{
    CreateGrid();
}

Map::~Map()
{
    delete [] grid;
}

int Map::GetSize() const
{
    return 500;
}

Node* Map::NodeAt(int x, int y)
{
    return grid[x][y];
}

void Map::CreateGrid()
{
    grid = new Node**[GetSize()];
    for(int x = 0; x < GetSize(); x++)
    {
        grid[x] = new Node*[GetSize()];
        for(int y = 0; y < GetSize(); y++)
        {
            grid[x][y] = new Node(x, y);
        }
    }
}
