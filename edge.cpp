#include "edge.h"

Edge::Edge():m_firstNode(nullptr), m_secondNode(nullptr){}

Edge::Edge(Node* f, Node* s):m_firstNode(f), m_secondNode(s){}

Node* Edge::getFirst()
{
    return m_firstNode;
}

Node* Edge::getSecond()
{
    return m_secondNode;
}

// bool Edge::contains(const Node* node) const {
//     return (node == &m_firstNode || node == &m_secondNode);
// }
