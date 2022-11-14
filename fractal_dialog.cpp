#include "fractal_dialog.h"
#include "ui_fractal_dialog.h"

Fractal_Dialog::Fractal_Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Fractal_Dialog)
{
  ui->setupUi(this);
  ui->IterationCheckBox->setCheckState(Qt::Checked);
  ui->IterationSpinBox->setEnabled(false);
  fillColorList();
}

Fractal_Dialog::~Fractal_Dialog()
{
  delete ui;
}

void Fractal_Dialog::fillColorList()
{
  QStringList colorList = QColor::colorNames();
  for(int i = 0; i < colorList.size(); i++)
    {
      QPixmap pix(QSize(40,20));
      pix.fill(QColor(colorList[i]));
      ui->comboBox->addItem(QIcon(pix), colorList[i]);
      ui->comboBox->setIconSize(QSize(40,20));
      ui->comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
}

double Fractal_Dialog::convertUnitOfMeasurent()
{
  double pixels = ui->spinBox->value();
  switch (ui->unitsComboBox->currentIndex())
    {
    case 0:
      {
        pixels = ui->spinBox->value();
        break;
      }
    case 1:
      {
        pixels = ui->spinBox->value() * CM_PIXEL_CONVERTION;
        break;
      }
    case 2:
      {
        pixels = ui->spinBox->value() * MM_PIXEL_CONVERTION;
        break;
      }
    }
  return pixels;
}

int Fractal_Dialog::getScaleStep()
{
  int scaleStep = DEFAULT_VALUE_FOR_PIXELS;
  switch (ui->unitsComboBox->currentIndex())
    {
    case 0:
      {
        scaleStep = DEFAULT_VALUE_FOR_PIXELS;
        break;
      }
    case 1:
      {
        scaleStep = CM_PIXEL_CONVERTION;
        break;
      }
    case 2:
      {
        scaleStep = CM_PIXEL_CONVERTION;
        break;
      }
    }
  return scaleStep;
}

void Fractal_Dialog::on_OkButton_clicked()
{
  ComplexNumber c(ui->RealSpinBox->value(), ui->ImaginarySpinBox->value());
  Fractal_Data * fractalData = new Fractal_Data(c, ui->spinBox->value(), getScaleStep(),
                                                ui->unitsComboBox->currentIndex(),
                                                ui->IterationSpinBox->value(),
                                                ui->comboBox->currentText());
  fractalDialogWindow = new Fractal_Dialog_Window();
  fractalDialogWindow->setFractalData(*fractalData);
  fractalDialogWindow->initializeWindow();
  fractalDialogWindow->initializeThread();
  fractalDialogWindow->renderThread();
  fractalDialogWindow->show();
  this->close();
}


void Fractal_Dialog::on_CancelButton_clicked()
{
  this->close();
}


void Fractal_Dialog::on_IterationCheckBox_stateChanged(int state)
{
  if(state == 0)
    {
      ui->IterationSpinBox->setEnabled(true);
    }
  else
    {
      ui->IterationSpinBox->setEnabled(false);
    }
}


void Fractal_Dialog::on_ScaleSlider_valueChanged(int value)
{
  ui->spinBox->setValue(value);
}

void Fractal_Dialog::on_spinBox_valueChanged(int arg1)
{
  ui->ScaleSlider->setValue((int)arg1);
}

void Fractal_Dialog::on_unitsComboBox_currentIndexChanged(int index)
{
  switch (index)
    {
    case 0:
      {
        ui->spinBox->setValue(DEFAULT_VALUE_FOR_PIXELS);
        ui->spinBox->setSingleStep(DEFAULT_VALUE_FOR_PIXELS);
        ui->spinBox->setMaximum(PIXEL_MAXIMUM);
        ui->ScaleSlider->setValue(DEFAULT_VALUE_FOR_PIXELS);
        ui->ScaleSlider->setSingleStep(DEFAULT_VALUE_FOR_PIXELS);
        ui->ScaleSlider->setMaximum(PIXEL_MAXIMUM);
        break;
      }
    case 1:
      {
        ui->spinBox->setValue(DEFAULT_VALUE_FOR_CM);
        ui->spinBox->setSingleStep(DEFAULT_VALUE_FOR_CM);
        ui->spinBox->setMaximum(CM_MAXIMUM);
        ui->ScaleSlider->setValue(DEFAULT_VALUE_FOR_CM);
        ui->ScaleSlider->setSingleStep(DEFAULT_VALUE_FOR_CM);
        ui->ScaleSlider->setMaximum(CM_MAXIMUM);
        break;
      }
    case 2:
      {
        ui->spinBox->setValue(DEFAULT_VALUE_FOR_MM);
        ui->spinBox->setSingleStep(DEFAULT_VALUE_FOR_MM);
        ui->spinBox->setMaximum(MM_MAXIMUM);
        ui->ScaleSlider->setValue(DEFAULT_VALUE_FOR_MM);
        ui->ScaleSlider->setSingleStep(DEFAULT_VALUE_FOR_MM);
        ui->ScaleSlider->setMaximum(MM_MAXIMUM);
        break;
      }
    }
}



