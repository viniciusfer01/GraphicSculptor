#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sculptor.h"
#include "plotter.h"
#include <cstdlib>
#include "QMessageBox"
#include "QProcess"
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

    ui->setupUi(this);
            ui->horizontalSliderDimX->setMaximum(ui->widget->sx-1);
            ui->horizontalSliderDimY->setMaximum(ui->widget->sy-1);
            ui->horizontalSliderDimZ->setMaximum(ui->widget->sz-1);
            ui->horizontalSliderRaio->setMaximum(ui->widget->sx/2 -1);
            ui->horizontalSliderRx->setMaximum(ui->widget->sx/2 -1);
            ui->horizontalSliderRy->setMaximum(ui->widget->sy/2 -1);
            ui->horizontalSliderRz->setMaximum(ui->widget->sz/2 -1);
            ui->horizontalSliderProf->setMaximum(ui->widget->sz -1);
            ui->horizontalSliderAlfa->setValue(10);
            ui->radioButtonPutVoxel->setChecked(true);

            connect(ui->horizontalSliderProf,
                                SIGNAL(valueChanged(int)),
                                ui->widget, //Envia a informação da interface para o desenho.
                                SLOT(changePlano(int)));

                        connect(ui->radioButtonPutVoxel,
                                SIGNAL(clicked(bool)),
                                this, //"This" refere-se ao MainWindown
                                SLOT(ChamaPutVoxel()));

                        connect(ui->radioButtonCutVoxel,
                                SIGNAL(clicked(bool)),
                                this,
                                SLOT(ChamaCutVoxel()));

                        connect(ui->radioButtonPutBox,
                                SIGNAL(clicked(bool)),
                                this,
                                SLOT(ChamaPutBox()));

                        connect(ui->radioButtonCutBox,
                                SIGNAL(clicked(bool)),
                                this,
                                SLOT(ChamaCutBox()));

                        connect(ui->radioButtonPutSphere,
                                SIGNAL(clicked(bool)),
                                this,
                                SLOT(ChamaPutSphere()));

                        connect(ui->radioButtonCutSphere,
                                SIGNAL(clicked(bool)),
                                this,
                                SLOT(ChamaCutSphere()));

                        connect(ui->radioButtonPutEllipsoid,
                                SIGNAL(clicked(bool)),
                                this,
                                SLOT(ChamaPutEllipsoid()));

                        connect(ui->radioButtonCutEllipsoid,
                                SIGNAL(clicked(bool)),
                                this,
                                SLOT(ChamaCutEllipsoid()));

                        connect(ui->horizontalSliderRed,
                                SIGNAL(valueChanged(int)),
                                ui->widget,
                                SLOT(changeRed(int)));

                        connect(ui->horizontalSliderBlue,
                                SIGNAL(valueChanged(int)),
                                ui->widget,
                                SLOT(changeBlue(int)));

                        connect(ui->horizontalSliderGreen,
                                SIGNAL(valueChanged(int)),
                                ui->widget,
                                SLOT(changeGreen(int)));

                        connect(ui->horizontalSliderAlfa,
                                SIGNAL(valueChanged(int)),
                                ui->widget,
                                SLOT(changeAlfa(int)));

                        connect(ui->horizontalSliderDimX,
                                SIGNAL(valueChanged(int)),
                                ui->widget,
                                SLOT(changeDimX(int)));

                        connect(ui->horizontalSliderDimY,
                                SIGNAL(valueChanged(int)),
                                ui->widget,
                                SLOT(changeDimY(int)));

                        connect(ui->horizontalSliderDimZ,
                                SIGNAL(valueChanged(int)),
                                ui->widget,
                                SLOT(changeDimZ(int)));

                        connect(ui->horizontalSliderRaio,
                                SIGNAL(valueChanged(int)),
                                ui->widget,
                                SLOT(changeRaio(int)));

                        connect(ui->horizontalSliderRx,
                                SIGNAL(valueChanged(int)),
                                ui->widget,
                                SLOT(changeRx(int)));

                        connect(ui->horizontalSliderRy,
                                SIGNAL(valueChanged(int)),
                                ui->widget,
                                SLOT(changeRy(int)));

                        connect(ui->horizontalSliderRz,
                                SIGNAL(valueChanged(int)),
                                ui->widget,
                                SLOT(changeRz(int)));

                        connect(ui->pushButtonXY,
                                SIGNAL(clicked(bool)),
                                this,
                                SLOT(EscolhePlanoXY()));

                        connect(ui->pushButtonYZ,
                                SIGNAL(clicked(bool)),
                                this,
                                SLOT(EscolhePlanoYZ()));

                        connect(ui->pushButtonXZ,
                                SIGNAL(clicked(bool)),
                                this,
                                SLOT(EscolhePlanoXZ()));

                        connect(ui->actionSave,
                                SIGNAL(triggered(bool)),
                                ui->widget,
                                SLOT(criaOff()));

                        connect(ui->pushButtonCriaCanvas,
                                SIGNAL(clicked(bool)),
                                this,
                                SLOT(CriaCanvas()));

                        connect(ui->horizontalSliderXCanvas,
                                SIGNAL(valueChanged(int)),
                                ui->widget,
                                SLOT(CriaCanvas()));

                        connect(ui->horizontalSliderYCanvas,
                                SIGNAL(valueChanged(int)),
                                ui->widget,
                                SLOT(CriaCanvas()));

                        connect(ui->horizontalSliderZCanvas,
                                SIGNAL(valueChanged(int)),
                                ui->widget,
                                SLOT(CriaCanvas()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::sair(){
    exit(0);
}

void MainWindow::CriaCanvas(){


      ui->widget->sx = ui->horizontalSliderXCanvas->value();
      ui->widget->sy = ui->horizontalSliderYCanvas->value();
      ui->widget->sz = ui->horizontalSliderZCanvas->value();
      ui->widget->s->~Sculptor();
      ui->widget->s = new Sculptor(ui->widget->sx,ui->widget->sy,ui->widget->sz);
      ui->horizontalSliderDimX->setMaximum(ui->widget->sx-1);
      ui->horizontalSliderDimY->setMaximum(ui->widget->sy-1);
      ui->horizontalSliderDimZ->setMaximum(ui->widget->sz-1);
      ui->horizontalSliderRaio->setMaximum(ui->widget->sx/2 -1);
      ui->horizontalSliderRx->setMaximum(ui->widget->sx/2 -1);
      ui->horizontalSliderRy->setMaximum(ui->widget->sy/2 -1);
      ui->horizontalSliderRz->setMaximum(ui->widget->sz/2 -1);
      ui->horizontalSliderProf->setMaximum(ui->widget->sz -1);
      ui->widget->repaint();
      ui->pushButtonXY->setChecked(true);
}


void MainWindow::EscolhePlanoXY(){  // Mostra o plano XY
    ui->widget->pl = XY;
    emit ui->widget->planeChosen(XY);
    ui->widget->dim = ui->widget->sz/2;
    ui->horizontalSliderProf->setMaximum(ui->widget->sz -1);
    ui->widget->repaint();
}

void MainWindow::EscolhePlanoYZ(){ //Mostrar o plano YZ
    ui->widget->pl = YZ;
    emit ui->widget->planeChosen(YZ);
    ui->widget->dim = ui->widget->sx/2;
    ui->horizontalSliderProf->setMaximum(ui->widget->sx -1);
    ui->widget->repaint();
}

void MainWindow::EscolhePlanoXZ(){ //Mostrar o plano XZ{
    ui->widget->pl = XZ;
    emit ui->widget->planeChosen(XZ);
    ui->widget->dim = ui->widget->sy/2;
    ui->horizontalSliderProf->setMaximum(ui->widget->sy -1);
    ui->widget->repaint();
}

void MainWindow::ChamaPutVoxel(){ //PutVoxel
    ui->widget->sh = 1;
}
void MainWindow::ChamaCutVoxel(){ //CutVoxel
    ui->widget->sh = 2;
}
void MainWindow::ChamaPutBox(){ //PutBox
    ui->widget->sh = 3;
}
void MainWindow::ChamaCutBox(){ //CutBox
    ui->widget->sh= 4;
}
void MainWindow::ChamaPutSphere(){ //PutSphere
    ui->widget->sh = 5;
}
void MainWindow::ChamaCutSphere(){ //CutSphere
    ui->widget->sh = 6;
}
void MainWindow::ChamaPutEllipsoid(){ //PutEllipsoid
    ui->widget->sh = 7;
}
void MainWindow::ChamaCutEllipsoid(){ //PutEllipsoid
    ui->widget->sh= 8;
}

