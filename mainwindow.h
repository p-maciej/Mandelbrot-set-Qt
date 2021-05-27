#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "renderer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        MainWindow(const MainWindow &thread) = delete;
        MainWindow& operator=(const MainWindow &thread) = delete;
        ~MainWindow();

    private slots:
            void on_pushButton_clicked();
            void on_moveLeft_clicked();
            void on_moveUp_clicked();
            void on_moveRight_clicked();
            void on_zoomOut_clicked();
            void on_moveDown_clicked();
            void on_zoomIn_clicked();

            void on_paletteComboBox_currentIndexChanged(int index);

private:
            Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
