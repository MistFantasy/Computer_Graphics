#include "triangle_data.h"

Triangle_Data::Triangle_Data(float triangleSize, float moveX, float moveY, float angle)
{
  this->triangleSize = triangleSize;
  this->moveX = moveX;
  this->moveY = moveY;
  this->angle = angle;
}

void Triangle_Data::setTriangleSize(float triangleSize)
{
  this->triangleSize = triangleSize;
}

void Triangle_Data::setMoveX(float moveX)
{
  this->moveX = moveX;
}

void Triangle_Data::setMoveY(float moveY)
{
  this->moveY = moveY;
}

void Triangle_Data::setAngle(float angle)
{
  this->angle = angle;
}

float Triangle_Data::getTriangleSize()
{
  return triangleSize;
}

float Triangle_Data::getMoveX()
{
  return moveX;
}

float Triangle_Data::getMoveY()
{
  return moveY;
}

float Triangle_Data::getAngle()
{
  return angle;
}
