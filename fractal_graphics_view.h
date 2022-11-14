#ifndef FRACTAL_GRAPHICS_VIEW_H
#define FRACTAL_GRAPHICS_VIEW_H

#include <QObject>
#include <QGraphicsView>

class Fractal_Graphics_View : public QGraphicsView
{
  Q_OBJECT;

public:
  Fractal_Graphics_View();

protected:
  void wheelEvent(QWheelEvent *event);
};

#endif // FRACTAL_GRAPHICS_VIEW_H
