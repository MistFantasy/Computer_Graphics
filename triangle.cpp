#include "triangle.h"

Triangle::Triangle() :
    QGraphicsItem()
{

}

Triangle::Triangle(int size) :
    QGraphicsItem()
{
  this->size = size;
}

void Triangle::setSize(int size)
{
  this->size = size;
}

void Triangle::setA(QPointF a)
{
  this->a = a;
}

void Triangle::setB(QPointF b)
{
  this->b = b;
}

void Triangle::setC(QPointF c)
{
  this->c = c;
}

Triangle::~Triangle()
{

}

QRectF Triangle::boundingRect() const
{
    return QRectF(-size / 2,-size / 2, size * 2, size * 2);
}



void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        QPolygonF polygon;
        //polygon << QPoint(0,-40) << QPoint(25,40) << QPoint(-25,40);
        polygon << QPointF(0, -size / 2)
                << QPointF(size / 2, size / 2)
                << QPointF(-size / 2, size / 2);
        painter->setBrush(Qt::black);
        painter->drawPolygon(polygon);
        Q_UNUSED(option);
        Q_UNUSED(widget);
}
