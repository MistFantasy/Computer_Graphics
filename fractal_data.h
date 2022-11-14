#ifndef FRACTAL_DATA_H
#define FRACTAL_DATA_H

#include <QPixmap>
#include "renderthread.h"
#include "complexnumber.h"
#include <QFile>

class Fractal_Data
{

public:
  Fractal_Data();
  Fractal_Data(ComplexNumber c, double curScale, int scaleStep,
               int unitOfMeasurement, int maxIter, QString colorOfFractal);
  ComplexNumber getConstant();
  QPixmap getPixmap();
  double getCurScale();
  int getMaxIter();
  QSize getSizeOfImage();
  void setSizeOfImage(QSize sizeOfImage);
  int getScaleStep();
  QString getColorOfFractal();
  int getUnitOfMeasurement();
  QSize getSizeOfWindow();
  QString getNameOfFile();
  void setSizeOfWindow(QSize sizeOfWindow);
  void setNameOfFile(QString nameOfFile);
  void setUnitOfMeasurement(int unitOfMeasurement);
  void setColorOfFractal(QString colorOfFractal);
  void setScaleStep(int scaleStep);
  void setMaxIter(int maxIter);
  void setConstant(ComplexNumber c);
  void setPixmap(QPixmap pixmap);
  void setCurScale(double curScale);
  void readFromFile(QString fileName);
  void writeToFile();
private:
  ComplexNumber c;
  int maxIter;
  QPixmap pixmap;
  double curScale;
  int scaleStep;
  int unitOfMeasurement;
  QSize sizeOfImage;
  QSize sizeOfWindow;
  QString colorOfFractal;
  QString nameOfFile;
};

#endif // FRACTAL_DATA_H
