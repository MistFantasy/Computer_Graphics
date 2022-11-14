#ifndef FRACTAL_DIALOG_H
#define FRACTAL_DIALOG_H



#define DEFAULT_VALUE_FOR_PIXELS 25
#define DEFAULT_VALUE_FOR_CM 1
#define DEFAULT_VALUE_FOR_MM 10
#define CM_PIXEL_CONVERTION 38
#define MM_PIXEL_CONVERTION 4
#define PIXEL_MAXIMUM 2000
#define CM_MAXIMUM 50
#define MM_MAXIMUM 500

#include <QDialog>
#include "fractal_dialog_window.h"

namespace Ui {
  class Fractal_Dialog;
}

class Fractal_Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Fractal_Dialog(QWidget *parent = nullptr);
  ~Fractal_Dialog();


private slots:
  void on_OkButton_clicked();

  void on_CancelButton_clicked();

  void on_IterationCheckBox_stateChanged(int state);

  void on_ScaleSlider_valueChanged(int value);

  void on_unitsComboBox_currentIndexChanged(int index);

  void on_spinBox_valueChanged(int arg1);

private:
  void fillColorList();
  double convertUnitOfMeasurent();
  int getScaleStep();
  Ui::Fractal_Dialog *ui;
  Fractal_Dialog_Window * fractalDialogWindow;
};

#endif // FRACTAL_DIALOG_H
