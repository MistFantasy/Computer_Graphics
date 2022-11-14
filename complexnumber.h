#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H
#include<math.h>


class ComplexNumber
{
public:
  ComplexNumber();
  ComplexNumber(double real, double imaginary);
  double getReal();
  double getImaginary();
  void setReal(double real);
  void setImaginary(double imaginary);
  double Mod();

  ComplexNumber operator *(ComplexNumber other);
  ComplexNumber operator +(ComplexNumber other);
private:
double real, imaginary;
};

#endif // COMPLEXNUMBER_H
