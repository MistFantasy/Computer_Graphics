#ifndef TRIANGLE_DIALOG_H
#define TRIANGLE_DIALOG_H

#include <QDialog>
#include "triangle_data.h"
#include "triangle_dialog_window.h"
namespace Ui {
  class Triangle_Dialog;
}

class Triangle_Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Triangle_Dialog(QWidget *parent = nullptr);
  ~Triangle_Dialog();

private slots:
  void on_buttonBox_accepted();

  void on_buttonBox_rejected();

private:
  Ui::Triangle_Dialog *ui;
  Triangle_Dialog_Window * triangleDialogWindow;
};

#endif // TRIANGLE_DIALOG_H
