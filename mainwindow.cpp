#include "mainwindow.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QPalette>

const int widgetWidth = 640;
const int widgetHeight = 640;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), m_picture(widgetWidth, widgetHeight)
{
    m_picture.fill(Qt::white);
    show();
    setFixedSize(widgetWidth, widgetHeight);
}

MainWindow::~MainWindow()
{

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if ( event -> button() == Qt::MouseButton::RightButton) {
        isDrawing = true;
        m_startPoint =  event -> pos();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if ( event -> button() == Qt::MouseButton::RightButton ) {
        m_curPoint = event -> pos();
        update();
        isDrawing = false;
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    QPalette pal;
    QBrush brush;

    if(isDrawing) {
        painter.begin(&m_buffer);
        brush.setTexture(m_buffer);
    }
    else {
        painter.begin(&m_picture);
        brush.setTexture(m_picture);
    }

    painter.setPen( QPen(Qt::black, 3) );
    painter.drawRect( QRect(m_startPoint, m_curPoint) );
    painter.end();
    pal.setBrush(QPalette::Active, QPalette::Window, brush);
    setPalette(pal);

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    m_buffer = m_picture;
    m_curPoint = event->pos();
    repaint();
}
