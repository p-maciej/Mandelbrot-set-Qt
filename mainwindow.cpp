#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->paletteComboBox->addItem(QString("Monochromatic"));
    ui->paletteComboBox->addItem(QString("Custom"));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    ui->picture->setMaxIterations(ui->iterations->value());
    ui->picture->draw();
}

void MainWindow::on_moveLeft_clicked() {
    ui->picture->setPosX(ui->picture->getPosX() - ui->moveStepSpinBox->value());
    ui->picture->draw();
}

void MainWindow::on_moveRight_clicked() {
    ui->picture->setPosX(ui->picture->getPosX() + ui->moveStepSpinBox->value());
    ui->picture->draw();
}

void MainWindow::on_moveUp_clicked() {
    ui->picture->setPosY(ui->picture->getPosY() - ui->moveStepSpinBox->value());
    ui->picture->draw();
}

void MainWindow::on_moveDown_clicked() {
    ui->picture->setPosY(ui->picture->getPosY() + ui->moveStepSpinBox->value());
    ui->picture->draw();
}

void MainWindow::on_zoomIn_clicked() {
    ui->picture->setZoom(ui->picture->getZoom() * (1 - ui->zoomStepSpinBox->value()));
    ui->picture->draw();
}

void MainWindow::on_zoomOut_clicked() {
    ui->picture->setZoom(ui->picture->getZoom() * (1 + ui->zoomStepSpinBox->value()));
    ui->picture->draw();
}


void MainWindow::on_paletteComboBox_currentIndexChanged(int index) {
    if(index == 0)
        ui->picture->setColorPalette(Renderer::ColorPalette::Monochromatic);
    else if(index == 1)
        ui->picture->setColorPalette(Renderer::ColorPalette::Custom);
}
