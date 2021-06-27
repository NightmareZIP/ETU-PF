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
    if (x >= 0 && x < GetSize() && y >= 0 && y < GetSize())
    {
        return grid[x][y];
    }
    return nullptr;
}

QVector<Node *> Map::GetNeighbours(Node *rootNode)
{
    QVector<Node*> neighbours;
    int x = rootNode->x;
    int y = rootNode->y;
    neighbours.append(NodeAt(x, y+1));
    neighbours.append(NodeAt(x+1, y));
    neighbours.append(NodeAt(x, y-1));
    neighbours.append(NodeAt(x-1, y));

    for (int i = neighbours.count() - 1; i >= 0; i--)
    {
        Node* n = neighbours.value(i);
        if (n == nullptr)
        {
            neighbours.removeAt(i);
        }
    }

    return neighbours;
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
