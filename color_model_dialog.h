#ifndef COLOR_MODEL_DIALOG_H
#define COLOR_MODEL_DIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QColorTransform>
#include <QFileDialog>


namespace Ui {
  class Color_Model_Dialog;
}

class Color_Model_Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Color_Model_Dialog(QWidget *parent = nullptr);
  ~Color_Model_Dialog();
  void setPixmap(QPixmap pixmap);
  QPixmap getPixmap();
  void setFileName(QString fileName);
  QString getFileName();
  void initializeWindow();

  void changeColorModel(QString whichModel);

  void cmykUiEnability(bool state);
  void rgbUiEnability(bool state);
  void changeBrushOnTheScene();
  void changingBrigtness(int valueOfBrigtness);
private slots:
  void on_cmykCheckBox_stateChanged(int arg1);

  void on_rgbCheckBox_stateChanged(int arg1);

  void on_redSlider_valueChanged(int value);

  void on_greenSlider_2_valueChanged(int value);

  void on_blueSlider_3_valueChanged(int value);

  void on_cyanSlider_4_valueChanged(int value);

  void on_magentaSlider_5_valueChanged(int value);

  void on_yellowSlider_6_valueChanged(int value);

  void on_blackSlider_7_valueChanged(int value);

  void on_redSpinBox_valueChanged(int arg1);

  void on_greenSpinBox_2_valueChanged(int arg1);

  void on_blueSpinBox_3_valueChanged(int arg1);

  void on_cyanSpinBox_4_valueChanged(int arg1);

  void on_magentaSpinBox_5_valueChanged(int arg1);

  void on_yellowSpinBox_6_valueChanged(int arg1);

  void on_blackSpinBox_7_valueChanged(int arg1);

  void on_pushButton_2_clicked();

  void on_BrightnessSlider_valueChanged(int value);

  void on_saveButton_clicked();

  void on_saveAsButton_clicked();

private:
  Ui::Color_Model_Dialog *ui;
  QGraphicsScene * imageScene, * colorScene;
  QBrush * brush;
  QPixmap pixmap, returnPixmap;
  QString fileName;
};

#endif // COLOR_MODEL_DIALOG_H
