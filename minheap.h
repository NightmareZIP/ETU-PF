#ifndef MINHEAP_H
#define MINHEAP_H


#include <vector>
#include <algorithm>
#include <stdexcept>
#include "node.h"

using namespace std;

// Data structure to store a min-heap node
struct MinHeap
{
public:
    int Count = 0;

    void Initialize(int maxSize)
    {
        items = vector<Node*>(maxSize);
    }

    void Add(Node* item)
    {
        item->heapIndex = Count;
        items[Count] = item;
        BubbleUp(item);
        Count++;
    }

    Node* RemoveFirst()
    {
        Node* first = items[0];
        Count--;
        items[0] = items[Count];
        items[0]->heapIndex=0;
        BubbleDown(items[0]);
        return first;
    }

    void UpdateItem(Node* item)
    {
        BubbleUp(item);
    }

    bool Contains(Node* item)
    {
        return items[item->heapIndex] == item;
    }

private:
    // vector to store heap elements
    vector<Node*> items;

    void BubbleDown(Node* item)
    {
        while (true)
        {
            int leftChild = item->heapIndex  * 2 + 1;
            int rightChild = item->heapIndex * 2 + 2;
            int swapIndex = 0;

            if (leftChild < Count)
            {
                swapIndex = leftChild;

                if (rightChild < Count && items[leftChild]->CompareTo(items[rightChild]) < 0)
                {
                        swapIndex = rightChild;
                }

                if (item->CompareTo(items[swapIndex]) < 0)
                {
                    Swap(item, items[swapIndex]);
                } else
                {
                    return;
                }
            }
            else
            {
                return;
            }
        }
    }

    void BubbleUp(Node* item)
    {
        int parentIndex = (item->heapIndex -1) /2;

        while (true)
        {
            Node* parentItem = items[parentIndex];
            if (item->CompareTo(parentItem) > 0)
            {
                Swap(item, parentItem);
            }
            else
            {
                break;
            }

            parentIndex = (item->heapIndex -1) /2;
        }
    }

    void Swap(Node* itemA, Node* itemB)
    {
        items[itemA->heapIndex] = itemB;
        items[itemB->heapIndex] = itemA;
        int itemAIndex = itemA->heapIndex;
        itemA->heapIndex = itemB->heapIndex;
        itemB->heapIndex = itemAIndex;
    }
};

#endif // MINHEAP_H
