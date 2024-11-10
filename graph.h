#ifndef GRAPH_H
#define GRAPH_H
#include "edge.h"
#include <vector>
#include <string_view>

class Graph
{
public:
    Graph();

    ~Graph();

    std::vector<Node*>& getNodes();

    std::vector<Edge>& getEdges();

    Node* m_draggedNode = nullptr;

    bool getOriented();

    void setOriented(bool set);

    double calcSquaredDistance(Node node, QPoint pos);

    Node* findNode(QPoint pos);

    bool validateDistanceExceptCurr(Node* currNode);

    bool validateDistance(QPoint pos);

    void addNode(QPoint p);

    bool verifyExistingEdge(Node* first, Node* second);

    void addEdge(Node* first, Node* second);

    void saveMAtoFile(const char* filename);

private:
    std::vector<Node*> m_nodes;
    std::vector<Edge> m_edges;
    std::vector<std::vector<int>> m_adMatrix;
    //lista de adiacenta
    bool m_isOriented = 0;

};

#endif // GRAPH_H
