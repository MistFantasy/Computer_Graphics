#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QObject>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QSize>
#include <QColor>
#include <QImage>
#include "complexnumber.h"
#include <QHash>


class RenderThread : public QThread
{
  Q_OBJECT

public:
  RenderThread(QObject *parent = 0);
  ~RenderThread();

  void render(ComplexNumber c, int maxIter,
              QSize resultSize, QColor colorOfFractal);
  double CalculateR(ComplexNumber c);
  QList<ComplexNumber> SqPolyIteration(ComplexNumber z0, ComplexNumber c, int maxIter,
                                       double radius);
  QColor ComplexHeatMap(double value, double min, double max, ComplexNumber z,
                        double radius, QColor colorOfFractal);
signals:
     void renderedImage(const QImage &image);

 protected:
     void run();

 private:
     QMutex mutex;
     QWaitCondition condition;
     QColor colorOfFractal;
     QSize resultSize;
     ComplexNumber c;
     int maxIter;
     bool restart;
     bool abort;
};

#endif // RENDERTHREAD_H
