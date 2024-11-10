#ifndef NODE_H
#define NODE_H

#include <QPoint>

class Node
{
public:
    Node();
    int getValue() const;
    QPoint getPos() const;
    void setValue(int val);
    void setPos(QPoint p);
    bool operator==(const Node& node);

private:
    int m_value;
    QPoint m_pos;
};

#endif // NODE_H
