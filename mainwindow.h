#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPaintEvent>
#include <iostream>
#include "graph.h"
#define rectWidth 20
#define rectHeight 20


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent* m);
    void mouseMoveEvent(QMouseEvent* m);
    void mouseReleaseEvent(QMouseEvent* m) override;
    void paintEvent(QPaintEvent* ev) override;

private slots:
    void onRadioButtonToggled(bool checked);
    void on_pushButton_clicked();
    void on_checkBox_released();

private:
    Ui::MainWindow *ui;

    Graph m_graph;
    Node* m_startNode;
    bool m_isFirstNodeSelected;
};
#endif // MAINWINDOW_H
