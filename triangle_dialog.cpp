#include "triangle_dialog.h"
#include "ui_triangle_dialog.h"

Triangle_Dialog::Triangle_Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Triangle_Dialog)
{
  ui->setupUi(this);
}

Triangle_Dialog::~Triangle_Dialog()
{
  delete ui;
}

void Triangle_Dialog::on_buttonBox_accepted()
{
  Triangle_Data * triangleData = new Triangle_Data(ui->triangleSizeSpinBox->value(),
                                                   ui->moveXSpinBox->value(),
                                                   ui->moveYSpinBox->value(),
                                                   ui->angleSpinBox->value());
  triangleDialogWindow = new Triangle_Dialog_Window();
  triangleDialogWindow->setTriangleData(triangleData);
  triangleDialogWindow->show();
  triangleDialogWindow->initializeWindow();
  this->close();
}


void Triangle_Dialog::on_buttonBox_rejected()
{
    ui->triangleSizeSpinBox->setValue(1);
    ui->moveXSpinBox->setValue(0);
    ui->moveYSpinBox->setValue(0);
    ui->angleSpinBox->setValue(0);
}

