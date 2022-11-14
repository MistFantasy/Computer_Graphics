#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fractal_dialog.h"
#include "triangle_dialog.h"
#include "fractal_dialog_window.h"
#include "color_model_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_actionFractal_triggered();

  void on_actionTriangle_triggered();

  void on_actionOpen_triggered();

  void on_actionImage_Color_Scheme_triggered();

private:
  Ui::MainWindow *ui;
  Fractal_Data * fractalData;
  Fractal_Dialog_Window * fractalDialogWindow;
  Fractal_Dialog * FractalDialog;
  Color_Model_Dialog * ColorModelDialog;
  Triangle_Dialog * TriangleDialog;
};
#endif // MAINWINDOW_H
