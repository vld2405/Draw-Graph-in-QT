#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_isFirstNodeSelected = false;
    ui->setupUi(this);
    connect(ui->orientedGraphRadioButton, &QRadioButton::toggled, this, &MainWindow::onRadioButtonToggled);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent* m)
{
    if (m->button() == Qt::MiddleButton)
    {
        std::vector<Node*>& nodes = m_graph.getNodes();
        for (auto& node : nodes)
        {
            if (QRect(node->getPos().x() - rectWidth / 2, node->getPos().y() - rectHeight / 2, rectWidth, rectHeight).contains(m->pos()))
            {
                m_graph.m_draggedNode = node;  // Track the node being dragged
                break;
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* m)
{
    if (m_graph.m_draggedNode)
    {
        QPoint previousPos = m_graph.m_draggedNode->getPos();
        m_graph.m_draggedNode->setPos(m->pos());

        if(!m_graph.validateDistanceExceptCurr(m_graph.m_draggedNode))
            m_graph.m_draggedNode->setPos(previousPos);

        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *m)
{
    if (m->button() == Qt::RightButton)
    {
        m_graph.addNode(m->pos());
        update();
    }
    else if (m->button() == Qt::LeftButton)
    {
        //adaug muchie
        auto nodes = m_graph.getNodes();
        for(auto& n : nodes)
        {
            if ((n->getPos().x() - m->pos().x()) *(n->getPos().x() - m->pos().x()) +
                    (n->getPos().y() - m->pos().y()) *(n->getPos().y() - m->pos().y()) < rectWidth * rectWidth/4)
            {
                if (m_isFirstNodeSelected)
                {
                    m_graph.addEdge(m_startNode, n);
                    m_isFirstNodeSelected = false;
                    update();
                }
                else
                {
                    m_startNode = n;
                    m_isFirstNodeSelected = true;
                }

            }
        }
    }
    else if (m->button() == Qt::MiddleButton && m_graph.m_draggedNode)
    {
        m_graph.m_draggedNode = nullptr;
        update();
    }
}

void MainWindow::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    std::vector<Node*>& nodes = m_graph.getNodes();
    for(auto&n : nodes)
    {
        QPen pen;
        pen.setColor(Qt::white);
        p.setPen(pen);

        QRect rect(n->getPos().x() - rectWidth/2, n->getPos().y() -rectHeight/2 , rectWidth, rectHeight);
        p.drawEllipse(rect);

        QString str;
        str = QString::number(n->getValue());

        p.drawText(rect, Qt::AlignCenter, str);

        pen.setColor(Qt::green);
        p.setPen(pen);
    }
    std::vector<Edge>& edges = m_graph.getEdges();
    for (auto& e:edges)
    {
        p.drawLine(e.getFirst()->getPos(), e.getSecond()->getPos());
        if(m_graph.getOriented() == true)
        {
            double angle = std::atan2(e.getSecond()->getPos().y() - e.getFirst()->getPos().y(), e.getSecond()->getPos().x() - e.getFirst()->getPos().x()); // Angle of the line
            int arrowSize = 20;

            QPoint arrowP1 = e.getSecond()->getPos() - QPoint(arrowSize * std::cos(angle - M_PI / 6),
                                                              arrowSize * std::sin(angle - M_PI / 6));
            QPoint arrowP2 = e.getSecond()->getPos() - QPoint(arrowSize * std::cos(angle + M_PI / 6),
                                                              arrowSize * std::sin(angle + M_PI / 6));

            p.drawLine(e.getSecond()->getPos(), arrowP1);
            p.drawLine(e.getSecond()->getPos(), arrowP2);
            p.drawLine(arrowP1, arrowP2);
        }
    }
}

void MainWindow::onRadioButtonToggled(bool checked)
{
    m_graph.setOriented(checked);
    update();
    m_graph.saveMAtoFile("../../matrAdiacenta.txt");
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_checkBox_released()
{

}

