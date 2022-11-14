#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QGraphicsItem>
#include <QPainter>


class Triangle : public QGraphicsItem
{
public:
    Triangle();
    ~Triangle();
    Triangle(int size);
    void setSize(int size);
    void setA(QPointF a);
    void setB(QPointF b);
    void setC(QPointF c);
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    int size;
    QPointF a;
    QPointF b;
    QPointF c;
};

#endif // TRIANGLE\_H
