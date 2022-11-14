#include "fractal_data.h"

Fractal_Data::Fractal_Data()
{
}

Fractal_Data::Fractal_Data(ComplexNumber c, double curScale, int scaleStep,
                           int unitOfMeasurement, int maxIter, QString colorOfFractal)
{
  this->c = c;
  this->curScale = curScale;
  this->scaleStep = scaleStep;
  this->unitOfMeasurement = unitOfMeasurement;
  this->maxIter = maxIter;
  this->colorOfFractal = colorOfFractal;
}

ComplexNumber Fractal_Data::getConstant()
{
  return this->c;
}

QPixmap Fractal_Data::getPixmap()
{
  return pixmap;
}

double Fractal_Data::getCurScale()
{
  return curScale;
}

int Fractal_Data::getMaxIter()
{
  return maxIter;
}

QSize Fractal_Data::getSizeOfImage()
{
  return sizeOfImage;
}

void Fractal_Data::setSizeOfImage(QSize sizeOfImage)
{
  this->sizeOfImage = sizeOfImage;
}

int Fractal_Data::getScaleStep()
{
  return scaleStep;
}

QString Fractal_Data::getColorOfFractal()
{
  return colorOfFractal;
}

int Fractal_Data::getUnitOfMeasurement()
{
  return unitOfMeasurement;
}

QSize Fractal_Data::getSizeOfWindow()
{
  return sizeOfWindow;
}

QString Fractal_Data::getNameOfFile()
{
  return nameOfFile;
}

void Fractal_Data::setSizeOfWindow(QSize sizeOfWindow)
{
  this->sizeOfWindow = sizeOfWindow;
}

void Fractal_Data::setNameOfFile(QString nameOfFile)
{
  this->nameOfFile = nameOfFile;
}

void Fractal_Data::setUnitOfMeasurement(int unitOfMeasurement)
{
  this->unitOfMeasurement = unitOfMeasurement;
}

void Fractal_Data::setColorOfFractal(QString colorOfFractal)
{
  this->colorOfFractal = colorOfFractal;
}

void Fractal_Data::setScaleStep(int scaleStep)
{
  this->scaleStep = scaleStep;
}

void Fractal_Data::setMaxIter(int maxIter)
{
  this->maxIter = maxIter;
}

void Fractal_Data::setConstant(ComplexNumber c)
{
  this->c = c;
}

void Fractal_Data::setPixmap(QPixmap pixmap)
{
  this->pixmap = pixmap;
}

void Fractal_Data::setCurScale(double curScale)
{
  this->curScale = curScale;
}

void Fractal_Data::readFromFile(QString fileName)
{
  this->nameOfFile = fileName;
  QFile inputFile(fileName);
  inputFile.open(QIODevice::ReadOnly);
  QDataStream in(&inputFile);
  double real, imaginary, curScale;
  int scaleStep, unitOfMeasurement, maxIter;
  QString colorOfFractal;
  QSize sizeOfImage;
  QSize sizeOfWindow;
  QPixmap pixmap;
  in >> real;
  in >> imaginary;
  in >> curScale;
  in >> scaleStep;
  in >> unitOfMeasurement;
  in >> colorOfFractal;
  in >> sizeOfImage;
  in >> sizeOfWindow;
  in >> pixmap;
  in >> maxIter;
  this->c.setReal(real);
  this->c.setImaginary(imaginary);
  this->curScale = curScale;
  this->scaleStep = scaleStep;
  this->unitOfMeasurement = unitOfMeasurement;
  this->colorOfFractal = colorOfFractal;
  this->sizeOfImage = sizeOfImage;
  this->sizeOfWindow = sizeOfWindow;
  this->pixmap = pixmap;
  this->maxIter = maxIter;
  inputFile.close();
}

void Fractal_Data::writeToFile()
{
  QFile outputFile(nameOfFile);
  outputFile.open(QIODevice::WriteOnly);
  QDataStream out(&outputFile);
  out << c.getReal();
  out << c.getImaginary();
  out << curScale;
  out << scaleStep;
  out << unitOfMeasurement;
  out << colorOfFractal;
  out << sizeOfImage;
  out << sizeOfWindow;
  out << pixmap;
  out << maxIter;
  outputFile.close();
}



