#include "triangle_dialog_window.h"
#include "ui_triangle_dialog_window.h"

Triangle_Dialog_Window::Triangle_Dialog_Window(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Triangle_Dialog_Window)
{
  ui->setupUi(this);
  scene = new QGraphicsScene();
  scene->setSceneRect(-ui->graphicsView->size().width(),
                      -ui->graphicsView->size().height(),
                      ui->graphicsView->size().width() * 2,
                      ui->graphicsView->size().height() * 2);
  ui->graphicsView->setScene(scene);
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &Triangle_Dialog_Window::renderTriangle);
  timer->start(80);
}

Triangle_Dialog_Window::~Triangle_Dialog_Window()
{
  delete ui;
}

void Triangle_Dialog_Window::setTriangleData(Triangle_Data * triangleData)
{
  this->triangleData = triangleData;
}

void Triangle_Dialog_Window::drawGrid()
{
  QPen pen;
  pen.setBrush(Qt::black);
  pen.setWidth(2);
  int viewWidth = ui->graphicsView->size().width();
  int viewHeight = ui->graphicsView->size().height();
  for (int i = -viewWidth; i < viewWidth; i += triangleData->getTriangleSize() / 2)
    {
      scene->addText(QString::number(i), QFont("Helvetica", 6))->setPos(i, 5);
//      scene->addLine(-viewWidth, i, viewWidth, -i,
//                     QPen(Qt::black));
    }
  for (int i = -viewHeight; i < viewHeight; i += triangleData->getTriangleSize() / 2)
    {
      scene->addText(QString::number(i), QFont("Helvetica", 6))->setPos(5, i);
//      scene->addLine(i, -viewHeight, -i, viewHeight,
//                     QPen(Qt::black));
    }
  scene->addLine(-viewWidth, 0, viewWidth, 0, pen);
  scene->addLine(0, -viewHeight, 0, viewHeight, pen);
}

void Triangle_Dialog_Window::renderTriangle()
{
  if(triangle->pos().x() < abs(triangleData->getMoveX()))
    {
      if(triangleData->getMoveX() > 0)
        {
          triangle->setX(triangle->pos().x() + STEP_CONSTANT);
        }
      else
        {
          triangle->setX(triangle->pos().x() - STEP_CONSTANT);
        }
    }
  if(triangle->pos().y() < abs(triangleData->getMoveY()))
    {
      if(triangleData->getMoveY() > 0)
        {
          triangle->setY(triangle->pos().y() + STEP_CONSTANT);
        }
      else
        {
          triangle->setY(triangle->pos().y() - STEP_CONSTANT);
        }
    }
  if(triangle->pos().x() >= abs(triangleData->getMoveX())
     && triangle->pos().y() >= abs(triangleData->getMoveY()))
    {
      if(abs(triangle->rotation()) > 359 && (int)triangle->rotation() % 360 == 0)
        {
          return;
        }
    }
  triangle->setRotation(triangle->rotation() + triangleData->getAngle());
}

void Triangle_Dialog_Window::initializeWindow()
{
  disconnect(ui->sizeSpinBox, SIGNAL(valueChanged(int)), this,
             SLOT(on_sizeSpinBox_valueChanged(int)));
  disconnect(ui->moveXSpinBox, SIGNAL(valueChanged(int)), this,
             SLOT(on_moveXSpinBox_valueChanged(int)));
  disconnect(ui->moveYSpinBox, SIGNAL(valueChanged(int)), this,
             SLOT(on_moveYSpinBox_valueChanged(int)));
  disconnect(ui->angleSpinBox, SIGNAL(valueChanged(int)), this,
             SLOT(on_angleSpinBox_valueChanged(int)));
  ui->sizeSpinBox->setValue(triangleData->getTriangleSize());
  ui->moveXSpinBox->setValue(triangleData->getMoveX());
  ui->moveYSpinBox->setValue(triangleData->getMoveY());
  ui->angleSpinBox->setValue(triangleData->getAngle());
  connect(ui->sizeSpinBox, SIGNAL(valueChanged(int)), this,
             SLOT(on_sizeSpinBox_valueChanged(int)));
  connect(ui->moveXSpinBox, SIGNAL(valueChanged(int)), this,
             SLOT(on_moveXSpinBox_valueChanged(int)));
  connect(ui->moveYSpinBox, SIGNAL(valueChanged(int)), this,
             SLOT(on_moveYSpinBox_valueChanged(int)));
  connect(ui->angleSpinBox, SIGNAL(valueChanged(int)), this,
             SLOT(on_angleSpinBox_valueChanged(int)));
  triangle = new Triangle(triangleData->getTriangleSize());
  scene->addItem(triangle);
  triangle->setPos(0, 0);
  drawGrid();
  renderTriangle();
}

void Triangle_Dialog_Window::on_sizeSpinBox_valueChanged(int arg1)
{
  triangle->setSize(arg1);
}


void Triangle_Dialog_Window::on_moveXSpinBox_valueChanged(int arg1)
{
  triangleData->setMoveX(arg1);
}


void Triangle_Dialog_Window::on_moveYSpinBox_valueChanged(int arg1)
{
  triangleData->setMoveY(arg1);
}


void Triangle_Dialog_Window::on_angleSpinBox_valueChanged(int arg1)
{
  triangleData->setAngle(arg1);
}


void Triangle_Dialog_Window::on_stopButton_clicked()
{
  timer->stop();
}


void Triangle_Dialog_Window::on_continueButton_clicked()
{
  timer->start();
}

