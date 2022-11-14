#include "fractal_dialog_window.h"
#include "ui_fractal_dialog_window.h"



Fractal_Dialog_Window::Fractal_Dialog_Window(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Fractal_Dialog_Window)
{
  ui->setupUi(this);  
  scene = new QGraphicsScene();
  scene->setSceneRect(0, 0, ui->graphicsView->size().width(), ui->graphicsView->size().height());
  ui->graphicsView->setScene(scene);
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setAttribute(Qt::WA_DeleteOnClose);   
  fillColorList();
}

Fractal_Dialog_Window::~Fractal_Dialog_Window()
{
  delete scene;
  delete fractalData;
  delete ui;
}

void Fractal_Dialog_Window::fillColorList()
{
  QStringList colorList = QColor::colorNames();
  for(int i = 0; i < colorList.size(); i++)
    {
      QPixmap pix(QSize(40,20));
      pix.fill(QColor(colorList[i]));
      ui->colorComboBox->addItem(QIcon(pix), colorList[i]);
      ui->colorComboBox->setIconSize(QSize(40,20));
      ui->colorComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
}

Fractal_Data &Fractal_Dialog_Window::getFractalData()
{
  return *fractalData;
}

void Fractal_Dialog_Window::setFractalData(Fractal_Data &fractalData)
{
  this->fractalData = &fractalData;
}

void Fractal_Dialog_Window::initializeWindow()
{
  disconnect(ui->scaleSpinBox, SIGNAL(valueChanged(int)), this,
             SLOT(on_scaleSpinBox_valueChanged(int)));
  disconnect(ui->scaleSlider, SIGNAL(valueChanged(int)), this,
             SLOT(on_scaleSlider_valueChanged(int)));
  ui->realSpinBox->setValue(fractalData->getConstant().getReal());
  ui->imaginarySpinBox->setValue(fractalData->getConstant().getImaginary());
  ui->colorComboBox->setCurrentText(fractalData->getColorOfFractal());
  ui->scaleComboBox->setCurrentIndex(fractalData->getUnitOfMeasurement());
  ui->scaleSpinBox->setValue(fractalData->getCurScale());
  ui->scaleSlider->setValue(fractalData->getCurScale());
  fractalData->setCurScale(convertUnitOfMeasurent());
  fractalData->setScaleStep(getScaleStep());
  connect(ui->scaleSpinBox, SIGNAL(valueChanged(int)), this,
          SLOT(on_scaleSpinBox_valueChanged(int)));
  connect(ui->scaleSlider, SIGNAL(valueChanged(int)), this,
          SLOT(on_scaleSlider_valueChanged(int)));
  ui->iterationSpinBox->setValue(fractalData->getMaxIter());
  fractalData->setSizeOfWindow(this->size());
  if(fractalData->getNameOfFile().isEmpty())
    {
      setWindowTitle("Множина Жюліа (Не збережено)");
    }
  else
    {
      setWindowTitle(fractalData->getNameOfFile().remove(".frc") + " (Збережено)");
    }
}

void Fractal_Dialog_Window::initializeThread()
{
  thread.setParent(this);
  qRegisterMetaType<QImage>("QImage");
  connect(&thread, SIGNAL(renderedImage(QImage)),
               this, SLOT(updatePixmap(QImage)));
}

void Fractal_Dialog_Window::renderThread()
{
  fractalData->setSizeOfImage(QSize(ui->graphicsView->size().width() + fractalData->getCurScale(),
                                    ui->graphicsView->size().height() + fractalData->getCurScale()));
  thread.render(fractalData->getConstant(), fractalData->getMaxIter(),
                fractalData->getSizeOfImage(), QColor(fractalData->getColorOfFractal()));
  ui->graphicsView->scene()->addText("Please wait. The image is uploading.");
}

void Fractal_Dialog_Window::updatePixmap(const QImage &image)
{
  fractalData->setPixmap(
        QPixmap::fromImage(image).copy(QRect(
        abs(fractalData->getSizeOfImage().width() - ui->graphicsView->size().width()) / 2,
        abs(fractalData->getSizeOfImage().height() - ui->graphicsView->size().height()) / 2,
        fractalData->getSizeOfImage().width(),
        fractalData->getSizeOfImage().height())));
  scene->clear();
  scene->addPixmap(fractalData->getPixmap());
}

void Fractal_Dialog_Window::wheelEvent(QWheelEvent *event)
{
  int numDegrees = event->angleDelta().y() / 8;
  if(fractalData->getCurScale() + numDegrees / 15.0f * fractalData->getScaleStep() >= 0)
    {
      fractalData->setCurScale(fractalData->getCurScale() + numDegrees / 15.0f * fractalData->getScaleStep());
      ui->scaleSlider->setValue(fractalData->getCurScale());
      renderThread();
    }
}

void Fractal_Dialog_Window::resizeEvent(QResizeEvent *event)
{
  Q_UNUSED(event);
  scene->setSceneRect(0, 0, ui->graphicsView->size().width(), ui->graphicsView->size().height());
  ui->graphicsView->setScene(scene);
  fractalData->setSizeOfWindow(this->size());
  renderThread();
}

double Fractal_Dialog_Window::convertUnitOfMeasurent()
{
  double pixels = ui->scaleSpinBox->value();
  switch (ui->scaleComboBox->currentIndex())
    {
    case 0:
      {
        pixels = ui->scaleSpinBox->value();
        break;
      }
    case 1:
      {
        pixels = ui->scaleSpinBox->value() * CM_PIXEL_CONVERTION;
        break;
      }
    case 2:
      {
        pixels = ui->scaleSpinBox->value() * MM_PIXEL_CONVERTION;
        break;
      }
    }
  return pixels;
}

int Fractal_Dialog_Window::getScaleStep()
{
  int scaleStep = DEFAULT_VALUE_FOR_PIXELS;
  switch (ui->scaleComboBox->currentIndex())
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

void Fractal_Dialog_Window::on_scaleComboBox_currentIndexChanged(int index)
{
  switch (index)
    {
    case 0:
      {
        ui->scaleSpinBox->setValue(DEFAULT_VALUE_FOR_PIXELS);
        ui->scaleSpinBox->setSingleStep(DEFAULT_VALUE_FOR_PIXELS);
        ui->scaleSpinBox->setMaximum(PIXEL_MAXIMUM);
        ui->scaleSlider->setValue(DEFAULT_VALUE_FOR_PIXELS);
        ui->scaleSlider->setSingleStep(DEFAULT_VALUE_FOR_PIXELS);
        ui->scaleSlider->setMaximum(PIXEL_MAXIMUM);
        break;
      }
    case 1:
      {
        ui->scaleSpinBox->setValue(DEFAULT_VALUE_FOR_CM);
        ui->scaleSpinBox->setSingleStep(DEFAULT_VALUE_FOR_CM);
        ui->scaleSpinBox->setMaximum(CM_MAXIMUM);
        ui->scaleSlider->setValue(DEFAULT_VALUE_FOR_CM);
        ui->scaleSlider->setSingleStep(DEFAULT_VALUE_FOR_CM);
        ui->scaleSlider->setMaximum(CM_MAXIMUM);
        break;
      }
    case 2:
      {
        ui->scaleSpinBox->setValue(DEFAULT_VALUE_FOR_MM);
        ui->scaleSpinBox->setSingleStep(DEFAULT_VALUE_FOR_MM);
        ui->scaleSpinBox->setMaximum(MM_MAXIMUM);
        ui->scaleSlider->setValue(DEFAULT_VALUE_FOR_MM);
        ui->scaleSlider->setSingleStep(DEFAULT_VALUE_FOR_MM);
        ui->scaleSlider->setMaximum(MM_MAXIMUM);
        break;
      }
    }
}


void Fractal_Dialog_Window::on_realSpinBox_valueChanged(double arg1)
{
  ComplexNumber newConstant(arg1, fractalData->getConstant().getImaginary());
  fractalData->setConstant(newConstant);
  renderThread();
}


void Fractal_Dialog_Window::on_imaginarySpinBox_valueChanged(double arg1)
{
  ComplexNumber newConstant(fractalData->getConstant().getReal(), arg1);
  fractalData->setConstant(newConstant);
  renderThread();
}


void Fractal_Dialog_Window::on_colorComboBox_currentIndexChanged(int index)
{
  if(ui->colorComboBox->count() == QColor::colorNames().size())
    {
      fractalData->setColorOfFractal(ui->colorComboBox->itemText(index));
      renderThread();
    }
}

void Fractal_Dialog_Window::on_scaleSlider_sliderReleased()
{
  fractalData->setCurScale(convertUnitOfMeasurent());
  fractalData->setScaleStep(getScaleStep());
  renderThread();
}

void Fractal_Dialog_Window::on_scaleSlider_valueChanged(int value)
{
  ui->scaleSpinBox->setValue(value);
}

void Fractal_Dialog_Window::on_scaleSpinBox_valueChanged(int arg1)
{
  ui->scaleSlider->setValue((int)arg1);
  fractalData->setCurScale(convertUnitOfMeasurent());
  fractalData->setScaleStep(getScaleStep());
  renderThread();
}


void Fractal_Dialog_Window::on_iterationSpinBox_valueChanged(int arg1)
{
  fractalData->setMaxIter(arg1);
  renderThread();
}


void Fractal_Dialog_Window::on_IterationBackwardButton_clicked()
{
  if(ui->iterationSpinBox->value() >= 1)
    {
      ui->iterationSpinBox->setValue(ui->iterationSpinBox->value() - 1);
      fractalData->setMaxIter(ui->iterationSpinBox->value());
      renderThread();
    }
}


void Fractal_Dialog_Window::on_IterationForwardButton_clicked()
{
  if(ui->iterationSpinBox->value() <= 5000)
    {
      ui->iterationSpinBox->setValue(ui->iterationSpinBox->value() + 1);
      fractalData->setMaxIter(ui->iterationSpinBox->value());
      renderThread();
    }
}

void Fractal_Dialog_Window::on_saveButton_clicked()
{
  if(fractalData->getNameOfFile().isEmpty())
    {
      on_saveAsButton_clicked();
    }
  else
    {
      fractalData->writeToFile();
      setWindowTitle(fractalData->getNameOfFile().remove(".frc") + " (Збережено)");
    }
}


void Fractal_Dialog_Window::on_saveAsButton_clicked()
{
  QString nameOfFile = QFileDialog::getSaveFileName(this, "Зберегти файл",
              "..\\", "Fractal Files (*.frc);; All Files (*.*)", nullptr, QFileDialog::DontUseNativeDialog);
  if(!nameOfFile.isEmpty())
    {
      nameOfFile += ".frc";
      fractalData->setNameOfFile(nameOfFile);
      fractalData->writeToFile();
      setWindowTitle(fractalData->getNameOfFile().remove(".frc") + " (Збережено)");
    }
}


void Fractal_Dialog_Window::on_HideButton_clicked()
{
  if(ui->frame->isVisible())
    {
      ui->HideButton->setText(">>");
      ui->frame->hide();
    }
  else
    {
      ui->HideButton->setText("<<");
      ui->frame->show();
    }
  ui->graphicsView->setScene(scene);
  renderThread();
}

