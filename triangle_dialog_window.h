#ifndef TRIANGLE_DIALOG_WINDOW_H
#define TRIANGLE_DIALOG_WINDOW_H

#include <QDialog>
#include <QGraphicsScene>
#include "triangle_data.h"
#include "triangle.h"
#include <QTimer>

#define STEP_CONSTANT 1
#define CONVERT_RADIAN 3.14 / 180


namespace Ui {
  class Triangle_Dialog_Window;
}

class Triangle_Dialog_Window : public QDialog
{
  Q_OBJECT

public:
  explicit Triangle_Dialog_Window(QWidget *parent = nullptr);
  ~Triangle_Dialog_Window();
  void setTriangleData(Triangle_Data *triangleData);
  void initializeWindow();
private slots:
  void on_sizeSpinBox_valueChanged(int arg1);

  void on_moveXSpinBox_valueChanged(int arg1);

  void on_moveYSpinBox_valueChanged(int arg1);

  void on_angleSpinBox_valueChanged(int arg1);

  void on_stopButton_clicked();

  void on_continueButton_clicked();

private:
  QTimer * timer;
  Ui::Triangle_Dialog_Window *ui;
  QGraphicsScene * scene;
  Triangle_Data * triangleData;
  Triangle * triangle;
  void renderTriangle();
  void drawGrid();
};

#endif // TRIANGLE_DIALOG_WINDOW_H
