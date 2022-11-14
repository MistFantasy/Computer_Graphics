#include "complexnumber.h"

ComplexNumber::ComplexNumber()
{

}

ComplexNumber::ComplexNumber(double real, double imaginary)
{
  this->real = real;
  this->imaginary = imaginary;
}

double ComplexNumber::getReal()
{
  return real;
}

double ComplexNumber::getImaginary()
{
  return imaginary;
}

void ComplexNumber::setReal(double real)
{
  this->real = real;
}

void ComplexNumber::setImaginary(double imaginary)
{
  this->imaginary = imaginary;
}

double ComplexNumber::Mod()
{
  return sqrt(real * real + imaginary * imaginary);
}

ComplexNumber ComplexNumber::operator *(ComplexNumber other)
{
  ComplexNumber complexNumber;
  complexNumber.setReal(this->real * other.getReal()
                        + (this->imaginary * other.getImaginary() * -1));
  complexNumber.setImaginary(this->imaginary * other.getReal() + this->real * other.getImaginary());
  return complexNumber;
}

ComplexNumber ComplexNumber::operator +(ComplexNumber other)
{
  ComplexNumber complexNumber;
  complexNumber.setReal(this->real + other.getReal());
  complexNumber.setImaginary(this->imaginary + other.getImaginary());
  return complexNumber;
}
