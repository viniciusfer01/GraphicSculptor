#include "color.h"
#include <QPainter>
#include <QBrush>
#include <QPen>

Color::Color(QWidget *parent) : QWidget(parent){

}

void Color::paintEvent(QPaintEvent *event){
    QPainter painter(this);
        QBrush brush;
        QPen pen;

        brush.setColor(QColor(r,g,b));
        brush.setStyle(Qt::SolidPattern);
        //Caneta preta
        pen.setColor(QColor(0,0,0));
        pen.setWidth(2);


        painter.setBrush(brush);
        painter.setPen(pen);

        painter.drawRect(0,0,width(),height());

}

void Color::set_r(int _r){
    r = _r;
    repaint();
}

void Color::set_g(int _g){
    g = _g;
    repaint();
}

void Color::set_b(int _b){
    b = _b;
    repaint();
}
