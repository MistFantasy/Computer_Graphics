#ifndef FRACTAL_DIALOG_WINDOW_H
#define FRACTAL_DIALOG_WINDOW_H

#include <QDialog>
#include <QGraphicsScene>
#include <QWheelEvent>
#include "renderthread.h"
#include "fractal_data.h"
#include <QComboBox>
#include <QToolBar>
#include <QFileDialog>


#define DEFAULT_VALUE_FOR_PIXELS 25
#define DEFAULT_VALUE_FOR_CM 1
#define DEFAULT_VALUE_FOR_MM 10
#define CM_PIXEL_CONVERTION 38
#define MM_PIXEL_CONVERTION 4
#define PIXEL_MAXIMUM 2000
#define CM_MAXIMUM 50
#define MM_MAXIMUM 500

namespace Ui {
  class Fractal_Dialog_Window;
}

class Fractal_Dialog_Window : public QDialog
{
  Q_OBJECT


public:
  explicit Fractal_Dialog_Window(QWidget *parent = nullptr);
  ~Fractal_Dialog_Window();

  Fractal_Data & getFractalData();
  void setFractalData(Fractal_Data & fractalData);

  void renderThread();
  void initializeThread();

  void initializeWindow();
private slots:
    void updatePixmap(const QImage &image);

    void on_scaleComboBox_currentIndexChanged(int index);

    void on_scaleSpinBox_valueChanged(int arg1);

    void on_realSpinBox_valueChanged(double arg1);

    void on_imaginarySpinBox_valueChanged(double arg1);

    void on_colorComboBox_currentIndexChanged(int index);

    void on_iterationSpinBox_valueChanged(int arg1);

    void on_IterationBackwardButton_clicked();

    void on_IterationForwardButton_clicked();

    void on_scaleSlider_sliderReleased();

    void on_scaleSlider_valueChanged(int value);

    void on_saveButton_clicked();

    void on_saveAsButton_clicked();

    void on_HideButton_clicked();

protected:
  void wheelEvent(QWheelEvent *event);
  void resizeEvent(QResizeEvent * event);
private:
  double convertUnitOfMeasurent();
  QGraphicsScene * scene;
  RenderThread thread;
  Ui::Fractal_Dialog_Window *ui;
  Fractal_Data * fractalData;
  int getScaleStep();
  void fillColorList();
};


#endif // FRACTAL_DIALOG_WINDOW_H
