#include "color_model_dialog.h"
#include "ui_color_model_dialog.h"

Color_Model_Dialog::Color_Model_Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Color_Model_Dialog)
{
  ui->setupUi(this);
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setAttribute(Qt::WA_DeleteOnClose);
}

Color_Model_Dialog::~Color_Model_Dialog()
{
  delete ui;
}

void Color_Model_Dialog::setPixmap(QPixmap pixmap)
{
  this->pixmap = pixmap;
}

QPixmap Color_Model_Dialog::getPixmap()
{
  return pixmap;
}

void Color_Model_Dialog::setFileName(QString fileName)
{
  this->fileName = fileName;
}

void Color_Model_Dialog::initializeWindow()
{
  this->setWindowTitle(fileName.split("\\").last());
  brush = new QBrush(Qt::black);
  rgbUiEnability(true);
  cmykUiEnability(false);
  colorScene = new QGraphicsScene();
//  qDebug()<< ui->graphicsView->size();
//  qDebug() << colorScene->sceneRect();
  colorScene->setSceneRect(-ui->graphicsView->size().width(),
                           -ui->graphicsView->size().height(),
                           ui->graphicsView->size().width(),
                           ui->graphicsView->size().height());
  colorScene->addRect(-ui->graphicsView->size().width(),
                      -ui->graphicsView->size().height(),
                      ui->graphicsView->size().width(),
                      ui->graphicsView->size().height(),
                      QPen(),
                      *brush);
//  qDebug() << colorScene->sceneRect();
//  qDebug() << ui->graphicsView->pos();
  ui->graphicsView->setScene(colorScene);
  imageScene = new QGraphicsScene();
  imageScene->setSceneRect(-ui->graphicsView_2->size().width() / 2,
                      -ui->graphicsView_2->size().height() / 2,
                      pixmap.size().width(),
                      pixmap.size().height());
  imageScene->addPixmap(pixmap);
  ui->graphicsView_2->setScene(imageScene);
}

int truncate(int value)
{
    if(value < 0) return 0;
    if(value > 255) return 255;

    return value;
}

void Color_Model_Dialog::changingBrigtness(int valueOfBrigtness)
{
  QImage image = pixmap.toImage();
  for(int i = 0; i < image.size().width(); i++)
    {
      for(int j = 0; j < image.size().height(); j++)
        {
          if(image.pixelColor(i, j).red() > image.pixelColor(i, j).blue()
             && image.pixelColor(i, j).green() > image.pixelColor(i, j).blue())
            {
              QColor color = image.pixelColor(i, j);
              color.setRgb(truncate(color.red() + valueOfBrigtness),
                           truncate(color.green() + valueOfBrigtness),
                           truncate(color.blue() + valueOfBrigtness));
              image.setPixelColor(i, j, color);
            }
        }
    }
  returnPixmap = QPixmap::fromImage(image);
  imageScene->clear();
  imageScene->addPixmap(QPixmap::fromImage(image));
}

QColor RGBtoCMYK(QColor color)
{
  QColor anotherColor;
  double dr, dg, db, k, c, m, y;
  qDebug() << color.red();
  qDebug() << color.green();
  qDebug() << color.blue();
  dr = (double)color.red() / 255;
  dg = (double)color.green() / 255;
  db = (double)color.blue() / 255;
  k = 1 - qMax(qMax(dr, dg), db);
  if((int)k == 1)
    {
      c = 0;
      m = 0;
      y = 0;
    }
  else
    {
      c = (1 - dr - k) / (1 - k);
      m = (1 - dg - k) / (1 - k);
      y = (1 - db - k) / (1 - k);
    }
  anotherColor.setCmykF(c, m, y, k);
  return anotherColor;
}

QColor CMYKtoRGB(QColor color)
{
  unsigned char r = (unsigned char)(255 * (1 - color.cyanF()) * (1 - color.blackF()));
  unsigned char g = (unsigned char)(255 * (1 - color.magentaF()) * (1 - color.blackF()));
  unsigned char b = (unsigned char)(255 * (1 - color.yellowF()) * (1 - color.blackF()));
  return QColor(r, g, b);
}

void Color_Model_Dialog::changeBrushOnTheScene()
{
  colorScene->clear();
  colorScene->addRect(-ui->graphicsView->size().width(),
                      -ui->graphicsView->size().height(),
                      ui->graphicsView->size().width(),
                      ui->graphicsView->size().height(),
                      QPen(),
                      *brush);
}

void Color_Model_Dialog::changeColorModel(QString whichModel)
{  
  if(whichModel.contains("rgbToCmyk"))
    {
      brush->setColor(brush->color().toCmyk());
    }
  if(whichModel.contains("cmykToRGB"))
    {
      brush->setColor(brush->color().toRgb());
    }
  changeBrushOnTheScene();
}



void Color_Model_Dialog::cmykUiEnability(bool state)
{
  ui->cmykCheckBox->setChecked(state);
  ui->cyanSlider_4->setEnabled(state);
  ui->magentaSlider_5->setEnabled(state);
  ui->yellowSlider_6->setEnabled(state);
  ui->blackSlider_7->setEnabled(state);
  ui->cyanSpinBox_4->setEnabled(state);
  ui->magentaSpinBox_5->setEnabled(state);
  ui->yellowSpinBox_6->setEnabled(state);
  ui->blackSpinBox_7->setEnabled(state);
}

void Color_Model_Dialog::rgbUiEnability(bool state)
{
  ui->rgbCheckBox->setChecked(state);
  ui->redSlider->setEnabled(state);
  ui->greenSlider_2->setEnabled(state);
  ui->blueSlider_3->setEnabled(state);
  ui->redSpinBox->setEnabled(state);
  ui->greenSpinBox_2->setEnabled(state);
  ui->blueSpinBox_3->setEnabled(state);
}

void Color_Model_Dialog::on_cmykCheckBox_stateChanged(int arg1)
{
  if(arg1 == 2)
    {
      cmykUiEnability(true);
      rgbUiEnability(false);
      changeColorModel("rgbToCmyk");
      ui->cyanSlider_4->setValue(brush->color().cyan());
      ui->magentaSlider_5->setValue(brush->color().magenta());
      ui->yellowSlider_6->setValue(brush->color().yellow());
      ui->blackSlider_7->setValue(brush->color().black());
    }
}


void Color_Model_Dialog::on_rgbCheckBox_stateChanged(int arg1)
{
  if(arg1 == 2)
    {
      cmykUiEnability(false);
      rgbUiEnability(true);
      changeColorModel("cmykToRGB");
      ui->redSlider->setValue(brush->color().red());
      ui->greenSlider_2->setValue(brush->color().green());
      ui->blueSlider_3->setValue(brush->color().blue());
    }
}

void Color_Model_Dialog::on_redSlider_valueChanged(int value)
{
  ui->redSpinBox->setValue(value);
  QColor colorOfTheBrush = brush->color();
  colorOfTheBrush.setRed(value);
  brush->setColor(colorOfTheBrush);
  changeBrushOnTheScene();
}

void Color_Model_Dialog::on_greenSlider_2_valueChanged(int value)
{
  ui->greenSpinBox_2->setValue(value);
  QColor colorOfTheBrush = brush->color();
  colorOfTheBrush.setGreen(value);
  brush->setColor(colorOfTheBrush);
  changeBrushOnTheScene();
}

void Color_Model_Dialog::on_blueSlider_3_valueChanged(int value)
{
  ui->blueSpinBox_3->setValue(value);
  QColor colorOfTheBrush = brush->color();
  colorOfTheBrush.setBlue(value);
  brush->setColor(colorOfTheBrush);
  changeBrushOnTheScene();
}


void Color_Model_Dialog::on_cyanSlider_4_valueChanged(int value)
{
  ui->cyanSpinBox_4->setValue(value);
  QColor colorOfTheBrush = brush->color();
  colorOfTheBrush.setCmyk(value, brush->color().magenta(),
                          brush->color().yellow(), brush->color().black());
  brush->setColor(colorOfTheBrush);
  changeBrushOnTheScene();
}


void Color_Model_Dialog::on_magentaSlider_5_valueChanged(int value)
{
  ui->magentaSpinBox_5->setValue(value);
  QColor colorOfTheBrush = brush->color();
  colorOfTheBrush.setCmyk(brush->color().cyan(), value,
                          brush->color().yellow(), brush->color().black());
  brush->setColor(colorOfTheBrush);
  changeBrushOnTheScene();
}


void Color_Model_Dialog::on_yellowSlider_6_valueChanged(int value)
{
  ui->yellowSpinBox_6->setValue(value);
  QColor colorOfTheBrush = brush->color();
  colorOfTheBrush.setCmyk(brush->color().cyan(), brush->color().magenta(),
                          value, brush->color().black());
  brush->setColor(colorOfTheBrush);
  changeBrushOnTheScene();
}


void Color_Model_Dialog::on_blackSlider_7_valueChanged(int value)
{
  ui->blackSpinBox_7->setValue(value);
  QColor colorOfTheBrush = brush->color();
  colorOfTheBrush.setCmyk(brush->color().cyan(), brush->color().magenta(),
                          brush->color().yellow(), value);
  brush->setColor(colorOfTheBrush);
  changeBrushOnTheScene();
}

void Color_Model_Dialog::on_redSpinBox_valueChanged(int arg1)
{
  emit ui->redSlider->valueChanged(arg1);
  ui->redSlider->setValue(arg1);
}


void Color_Model_Dialog::on_greenSpinBox_2_valueChanged(int arg1)
{
  emit ui->greenSlider_2->valueChanged(arg1);
  ui->greenSlider_2->setValue(arg1);
}


void Color_Model_Dialog::on_blueSpinBox_3_valueChanged(int arg1)
{
  emit ui->blueSlider_3->valueChanged(arg1);
  ui->blueSlider_3->setValue(arg1);
}


void Color_Model_Dialog::on_cyanSpinBox_4_valueChanged(int arg1)
{
  emit ui->cyanSlider_4->valueChanged(arg1);
  ui->cyanSlider_4->setValue(arg1);
}


void Color_Model_Dialog::on_magentaSpinBox_5_valueChanged(int arg1)
{
  emit ui->magentaSlider_5->valueChanged(arg1);
  ui->magentaSlider_5->setValue(arg1);
}


void Color_Model_Dialog::on_yellowSpinBox_6_valueChanged(int arg1)
{
  emit ui->yellowSlider_6->valueChanged(arg1);
  ui->yellowSlider_6->setValue(arg1);
}


void Color_Model_Dialog::on_blackSpinBox_7_valueChanged(int arg1)
{
  emit ui->blackSlider_7->valueChanged(arg1);
  ui->blackSlider_7->setValue(arg1);
}


void Color_Model_Dialog::on_pushButton_2_clicked()
{
  this->close();
}


void Color_Model_Dialog::on_BrightnessSlider_valueChanged(int value)
{
  changingBrigtness(value);
}


void Color_Model_Dialog::on_saveButton_clicked()
{
  qDebug()<< returnPixmap.save(fileName);
}


void Color_Model_Dialog::on_saveAsButton_clicked()
{
  QString selectedFilter;
  QString nameOfFile = QFileDialog::getSaveFileName(this, "Зберегти файл",
              "..\\", "Jpeg Files (*.jpg);; Png Files (*.png);; "
"Bmp Files (*.bmp);; All Files (*.*)", &selectedFilter, QFileDialog::DontUseNativeDialog);
  if(!nameOfFile.isEmpty())
    {
      qDebug() << selectedFilter;
      fileName = nameOfFile + selectedFilter;
      qDebug() << returnPixmap.save(fileName);
    }
}

