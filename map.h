#ifndef MAP_H
#define MAP_H

#include <node.h>
#include <qvector.h>

class Map
{
public:
    Map();
    ~Map();

    Node*** grid;
    int GetSize() const;
    Node* NodeAt(int x, int y);

private:
    void CreateGrid();

};

#endif // MAP_H
