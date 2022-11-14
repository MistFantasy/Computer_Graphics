#include "renderthread.h"

RenderThread::RenderThread(QObject *parent)
     : QThread(parent)
 {
     restart = false;
     abort = false;
 }

RenderThread::~RenderThread()
 {
     mutex.lock();
     abort = true;
     condition.wakeOne();
     mutex.unlock();

     wait();
 }

void RenderThread::render(ComplexNumber c, int maxIter,
                           QSize resultSize, QColor colorOfFractal)
 {
     QMutexLocker locker(&mutex);

     this->resultSize = resultSize;
     this->c = c;
     this->maxIter = maxIter;
     this->colorOfFractal = colorOfFractal;
     if (!isRunning()) {
         start(LowPriority);
     } else {
         restart = true;
         condition.wakeOne();
     }
 }

double RenderThread::CalculateR(ComplexNumber c)
{
  return (1 + sqrt(1 + 4 * c.Mod())) / 2;
}

QList<ComplexNumber> RenderThread::SqPolyIteration(ComplexNumber z0, ComplexNumber c, int maxIter, double radius)
{
    QList<ComplexNumber> res = QList<ComplexNumber>();
    res.append(z0);
    for (int i = 0; i < maxIter; i++)
    {
        if (radius > 0)
        {
            if(res.last().Mod() > radius)
              {
                break;
              }
        }
        res.append(res.last() * res.last() + c);
    }
    return res;
}

QColor RenderThread::ComplexHeatMap(double value, double min, double max,
                                    ComplexNumber z, double radius, QColor colorOfFractal)
{
  QColor color;
  double val = (value - min) / (max - min);
  color.setRgb(colorOfFractal.red() * val,
               colorOfFractal.green() * (1 - val),
               colorOfFractal.blue() * (z.Mod() / radius > 1 ? 1 : z.Mod() / radius));
  return color;
}

void RenderThread::run()
{
  forever
  {
    mutex.lock();
    ComplexNumber c = this->c;
    int maxIter = this->maxIter;
    QSize resultSize = this->resultSize;
    QColor colorOfFractal = this->colorOfFractal;
    mutex.unlock();
    double radius = CalculateR(c);
    double xMin = -radius;
    double yMin = -radius;
    double xMax = radius;
    double yMax = radius;
    double xStep = abs(xMax - xMin) / resultSize.width();
    double yStep = abs(yMax - yMin) / resultSize.height();
    QImage image(resultSize, QImage::Format_RGB32);

    QHash<int, QHash<int, int>> xyIdx = QHash<int, QHash<int, int>>();
    while (!restart)
      {
        if (restart)
          break;
        if (abort)
          return;
        int maxIdx = 0;
        for(int i = 0; i < resultSize.width(); i++)
          {
            xyIdx.insert(i, QHash<int, int>());
            for(int j = 0; j < resultSize.height(); j++)
              {
                double x = xMin + i * xStep;
                double y = yMin + j * yStep;
                ComplexNumber z = ComplexNumber(x, y);
                QList<ComplexNumber> zIter = SqPolyIteration(z, c, maxIter, radius);
                int idx = zIter.size() - 1;
                if(maxIdx < idx)
                  {
                    maxIdx = idx;
                  }
                xyIdx[i].insert(j, idx);
              }
          }
        for (int i = 0; i < resultSize.width(); i++)
          {
            for (int j = 0; j < resultSize.height(); j++)
              {
                int idx = xyIdx[i][j];
                double x = xMin + i * xStep;
                double y = yMin + j * yStep;
                ComplexNumber z = ComplexNumber(x, y);
                image.setPixel(resultSize.width() - i - 1, j, ComplexHeatMap(idx, 0, maxIdx, z, radius,
                                                                             colorOfFractal).rgb());
              }
          }
        if (!restart)
          emit renderedImage(image);
      }
    mutex.lock();
    if (!restart)
      condition.wait(&mutex);
    restart = false;
    mutex.unlock();
  }
}
