#include "node.h"

Node::Node() {}

int Node::getValue() const
{
    return m_value;
}

QPoint Node::getPos() const
{
    return m_pos;
}

void Node::setValue(int val)
{
    m_value = val;
}

void Node::setPos(QPoint p)
{
    m_pos = p;
}

bool Node::operator==(const Node& node)
{
    if((this->getPos().x() == node.getPos().x() && this->getPos().y() == node.getPos().y()) || this->getValue() == node.getValue())
        return 1;
    return 0;
}
