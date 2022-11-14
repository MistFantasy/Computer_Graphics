#ifndef TRIANGLE_DATA_H
#define TRIANGLE_DATA_H


class Triangle_Data
{
public:
  Triangle_Data();
  Triangle_Data(float triangleSize, float moveX, float moveY, float angle);
  void setTriangleSize(float triangleSize);
  void setMoveX(float moveX);
  void setMoveY(float moveY);
  void setAngle(float angle);
  float getTriangleSize();
  float getMoveX();
  float getMoveY();
  float getAngle();
private:
  float triangleSize;
  float moveX;
  float moveY;
  float angle;
};

#endif // TRIANGLE_DATA_H
