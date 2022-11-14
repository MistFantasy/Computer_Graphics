#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  FractalDialog = new Fractal_Dialog(this);
  TriangleDialog = new Triangle_Dialog(this);
  ColorModelDialog = new Color_Model_Dialog(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_actionFractal_triggered()
{
  FractalDialog->setModal(true);
  FractalDialog->exec();
}


void MainWindow::on_actionTriangle_triggered()
{
  TriangleDialog->setModal(true);
  TriangleDialog->exec();
}

void MainWindow::on_actionImage_Color_Scheme_triggered()
{
  QString FileName;
  FileName = QFileDialog::getOpenFileName(this, "Відкрити файл",
  "..\\", "Jpeg Images (*.jpg);; Png Images (*.png);; "
"BitMap Images (*.bmp);; All Files (*.*)", nullptr, QFileDialog::DontUseNativeDialog);
  if(!FileName.isEmpty() && (FileName.contains(".jpg")
                             || FileName.contains(".png")
                             || FileName.contains(".bmp")))
    {
      ColorModelDialog = new Color_Model_Dialog();
      ColorModelDialog->setFileName(FileName);
      ColorModelDialog->setPixmap(FileName);      
      ColorModelDialog->show();
      ColorModelDialog->initializeWindow();
    }

}

void MainWindow::on_actionOpen_triggered()
{
  QString FileName;
  FileName = QFileDialog::getOpenFileName(this, "Відкрити файл",
  "..\\", "Fractal Files (*.frc);; All Files (*.*)", nullptr, QFileDialog::DontUseNativeDialog);
  if(!FileName.isEmpty() && FileName.contains(".frc"))
    {
      fractalData = new Fractal_Data();
      fractalData->readFromFile(FileName);
      fractalDialogWindow = new Fractal_Dialog_Window();
      fractalDialogWindow->setFractalData(*fractalData);
      fractalDialogWindow->initializeWindow();
      fractalDialogWindow->initializeThread();
      fractalDialogWindow->renderThread();
      fractalDialogWindow->show();
    }
}


