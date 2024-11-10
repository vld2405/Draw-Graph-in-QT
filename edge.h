#ifndef EDGE_H
#define EDGE_H

#include "node.h"

class Edge
{
public:
    Edge();
    Edge(Node* f, Node* s);
    Node* getFirst();
    Node* getSecond();
    //bool contains(const Node* node) const;

private:
    Node* m_firstNode, *m_secondNode;
};

#endif // EDGE_H
