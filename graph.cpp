#include "graph.h"
#include "mainwindow.h"
#include <QDebug>
#include <fstream>

Graph::Graph(){}

Graph::~Graph()
{
    for(Node* node: m_nodes)
    {
        delete node;
    }
}

std::vector<Node*>& Graph::getNodes()
{
    return m_nodes;
}

std::vector<Edge>& Graph::getEdges()
{
    return m_edges;
}

bool Graph::getOriented()
{
    return m_isOriented;
}

void Graph::setOriented(bool set)
{
    m_isOriented = set;
}

double Graph::calcSquaredDistance(Node node, QPoint pos)
{
    return (node.getPos().x() - pos.x()) * (node.getPos().x() - pos.x()) + (node.getPos().y() - pos.y()) * (node.getPos().y() - pos.y());
}

Node* Graph::findNode(QPoint pos)
{
    std::vector<Node*>& nodes = getNodes();

    for(auto node: nodes)
        if(node->getPos() == pos)
            return node;

    return nullptr;
}

bool Graph::validateDistanceExceptCurr(Node* currNode)
{
    std::vector<Node*>& nodes = getNodes();

    for(int i=0; i < nodes.size(); ++i)
    {
        if(currNode == nodes[i])
            continue;

        if(Graph::calcSquaredDistance(*(nodes[i]), currNode->getPos()) <= rectHeight * rectHeight)
            return 0;
    }
    return 1;
}

bool Graph::validateDistance(QPoint pos)
{
    std::vector<Node*>& nodes = getNodes();

    for(int i=0; i < nodes.size(); ++i)
    {
        if(Graph::calcSquaredDistance(*(nodes[i]), pos) <= rectHeight * rectHeight)
            return 0;
    }
    return 1;
}

void Graph::addNode(QPoint p)
{
    if(Graph::validateDistance(p))
    {
        Node* n = new Node();
        n->setPos(p);
        n->setValue(m_nodes.size() + 1);
        m_nodes.push_back(n);
        saveMAtoFile("../../matrAdiacenta.txt");
    }
    else
    {
        qDebug() << "Too close to an existing node";
    }
}

bool Graph::verifyExistingEdge(Node* first, Node* second)
{
    std::vector<Edge>& edges = Graph::getEdges();
    for(int i=0; i < edges.size(); ++i)
    {
        if(edges[i].getFirst() == first && edges[i].getSecond() == second)
            return true;

        if(m_isOriented == false && edges[i].getFirst() == second && edges[i].getSecond() == first)
            return true;
    }
    return false;
}

void Graph::addEdge(Node* first, Node* second)
{
    if(!Graph::verifyExistingEdge(first, second))
    {
        Edge e(first, second);
        m_edges.push_back(e);
        saveMAtoFile("../../matrAdiacenta.txt");
    }
    else
    {
        qDebug() << "Existing Edge";
    }
}

void Graph::saveMAtoFile(const char* filename)
{
    std::ofstream fout(filename);

    int nodesCounter = m_nodes.size();

    std::vector<std::vector<int>> adMatrix(nodesCounter, std::vector<int> (nodesCounter, 0));

    fout << nodesCounter << '\n';

    for(auto edge: m_edges)
    {
        int node1 = edge.getFirst()->getValue() - 1, node2 = edge.getSecond()->getValue() - 1;


        if(m_isOriented == 0 && node1 != node2)
        {
            adMatrix[node1][node2] = 1;
            adMatrix[node2][node1] = 1;
        }
        else if(m_isOriented == 1)
        {
            adMatrix[node1][node2] = 1;
        }
    }

    for(int i=0; i < nodesCounter; ++i)
    {
        for(int j=0; j < nodesCounter; ++j)
        {
            fout << adMatrix[i][j] << " ";
        }
        fout << '\n';
    }
    m_adMatrix = adMatrix;
    fout.close();
}
