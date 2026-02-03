#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include "qcustomplot.h"
#include <QIcon>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double xvalue;
    double layers;
    double epoch;
    double groups;
    QStringList list;
    bool is_matrix;
    bool IsClickedCommandButton;
public Q_SLOTS:
    void Recognize();
    void bmp_file_dialog();
    void selectDrawMode();
    void selectFileMode();
    void changeValueOfSlider();
    void changeValueOfSlider2();
    void changeValueOfSlider3();
    void changeValueOfSlider4();

private slots:
    void on_commandLinkButton_clicked();

    //void on_horizontalSlider_sliderMoved(int position);

    //void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_radioButtonMatrix_clicked();

    void on_radioButtonGraph_clicked();

    void on_pushButton_2_clicked();

    void on_uploadFileButton_clicked();

    void on_runButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
