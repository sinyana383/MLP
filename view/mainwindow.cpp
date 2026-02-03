#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::Recognize()
{

    if (!(ui->paintWidjet->Pixels_draw.empty()) && ui->drawRadioButton->isChecked())
    {
        //QMessageBox::about(this,"test output", QString::number(ui->paintWidjet->Pixels[1]));//здесь нужно вызвать функцию распознавания
        ui->prediction->setText("U");
        ui->paintWidjet->Pixels_draw.clear();
    }

    else if (!(ui->paintWidjet->Pixels_file.empty()) && ui->bmpRadioButton->isChecked())
    {
        //QMessageBox::about(this,"test output", QString::number(ui->paintWidjet->Pixels[1]));//здесь нужно вызвать функцию распознавания
        ui->prediction->setText("G");
        ui->paintWidjet->Pixels_file.clear();
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/Perceptron-or-task.png"));
    this->setWindowTitle("MLP");
    ui->browseButton->setEnabled(false);

    connect(ui->recognizeButton, SIGNAL (clicked()), this, SLOT (Recognize()));
    connect(ui->drawRadioButton, SIGNAL (clicked()), this, SLOT (selectDrawMode()));
    connect(ui->bmpRadioButton, SIGNAL (clicked()), this, SLOT (selectFileMode()));
    connect(ui->browseButton, SIGNAL (clicked()), this, SLOT (bmp_file_dialog()));

    //connect(ui->radioButton_3, SIGNAL (clicked()), this, SLOT (selectFileMode()));
    //connect(ui->horizontalSlider, SIGNAL (sliderMoved(int)), this, SLOT(changeValueOfSlider()));
    connect(ui->horizontalSlider_2, SIGNAL (valueChanged(int)), this, SLOT(changeValueOfSlider2()));
    connect(ui->horizontalSlider, SIGNAL (valueChanged(int)), this, SLOT(changeValueOfSlider()));
    connect(ui->horizontalSlider_3, SIGNAL (valueChanged(int)), this, SLOT(changeValueOfSlider3()));
    connect(ui->horizontalSlider_4, SIGNAL (valueChanged(int)), this, SLOT(changeValueOfSlider4()));
    ui->horizontalSlider->setRange(0,100);
    ui->horizontalSlider_2->setRange(2,5);
    ui->horizontalSlider_3->setRange(1, 10);
    ui->horizontalSlider_4->setRange(1, 10);
    xvalue = ui->horizontalSlider->value();
    layers = ui->horizontalSlider_2->value();
    epoch = ui->horizontalSlider_3->value();
    groups = ui->horizontalSlider_4->value();
    //QLabel *label = new QLabel(this);
    ui->label_19->setText(QString::number(xvalue/100));
    ui->label_2->setText(QString::number(layers));
    ui->label_23->setText(QString::number(epoch));
    ui->label_25->setText(QString::number(groups));

    ui->secondPred->setStyleSheet("color: rgba(255, 255, 255, 0.5);");
    ui->thirdPred->setStyleSheet("color: rgba(255, 255, 255, 0.25);");
    ui->forthPred->setStyleSheet("color: rgba(255, 255, 255, 0.125);");

    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    ui->functionWidjet->addGraph();
    ui->functionWidjet->graph(0)->addData(x,y);
    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(188, 190, 251));
    ui->functionWidjet->graph(0)->setPen(pen);
    //ui->functionWidjet->graph(0)->setPen(Qcolor)
    ui->functionWidjet->yAxis->grid()->setVisible(false);
    ui->functionWidjet->xAxis->grid()->setVisible(false);
    ui->functionWidjet->xAxis->setLabel("EPOCH");
    ui->functionWidjet->yAxis->setLabel("ERROR VALUE");
    ui->functionWidjet->yAxis->setRange(*std::min_element(y.begin(), y.end()),*std::max_element(y.begin(), y.end()));
    ui->functionWidjet->xAxis->setRange(0,*std::max_element(x.begin(), x.end()));
    ui->functionWidjet->setBackground(QColor(190, 251, 188));
    //ui->functionWidjet->replot();
    //ui->functionWidjet->setBackground(Color::yellow)
    ui->trainLayoutWidget->hide();
    ui->label_19->setWordWrap(true);
    ui->commandLinkButton->setIcon(QIcon(":/images/settings-gear.png"));
    //ui->commandLinkButton->setStyleSheet("QCommandLinkButton {color: black;}");
    //ui->commandLinkButton->setStyleSheet("QCommandLinkButton::hover::text {color: yellow;}");
    IsClickedCommandButton = false;
    ui->accuracy->setText("--");
    ui->fmeasure->setText("--");
    ui->recall->setText("--");
    ui->time->setText("--");
    ui->precision->setText("--");
    is_matrix = ui->radioButtonMatrix->isChecked();
}

void MainWindow::changeValueOfSlider()
{
    xvalue = ui->horizontalSlider->value();
    ui->label_19->setText(QString::number(xvalue/100));
}

void MainWindow::bmp_file_dialog() {
    QImage img = QImage(
        QFileDialog::getOpenFileName(this, tr("Open File"), "/path/to/file/", tr("Object Files (*.bmp)")));
    if (img.isNull())
    {
        return;
    }
    if (img.size().width() != img.size().height() || img.size().width() > 512 || img.size().height() > 512 ||
        img.size().width() < 28 || img.size().height() < 28) {
        QMessageBox::about(this, "Ошибка",
                           "Выберите квадратное изображение .bmp не меньше "
                           "28x28 и не больше 512x512");
    } else {
        ui->paintWidjet->Pixels_file.clear();
        ui->paintWidjet->setEnabled(false);
        img = img.scaled(28, 28);
        img = img.transformed(QTransform().rotate(-90));

        ui->paintWidjet->Pixels_file.push_back(15);
        for (int i = img.size().width() - 1; i >= 0; i--) {
            for (int j = 0; j < img.size().height(); j++) {
                ui->paintWidjet->Pixels_file.push_back(img.pixelColor(j, i).black());
            }
        }
    }
}

void MainWindow::selectDrawMode()
{
    ui->paintWidjet->setEnabled(true);
    ui->browseButton->setEnabled(false);
}

void MainWindow::selectFileMode()
{
    ui->paintWidjet->setEnabled(false);
    ui->browseButton->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_commandLinkButton_clicked()
{
    if (!IsClickedCommandButton)
    {
        ui->fileLabel->setText("Train file");
        ui->runButton->setText("Run train");
        ui->testLayout->hide();
        ui->trainLayoutWidget->show();
        IsClickedCommandButton = true;
    }
    else
    {
        ui->fileLabel->setText("Test file");
        ui->runButton->setText("Run test");
        ui->trainLayoutWidget->hide();
        ui->testLayout->show();
        IsClickedCommandButton = false;
    }

}

void MainWindow::changeValueOfSlider2()
{
    layers = ui->horizontalSlider_2->value();
    ui->label_2->setText(QString::number(layers));
}

void MainWindow::changeValueOfSlider3()
{
    epoch = ui->horizontalSlider_3->value();
    ui->label_23->setText(QString::number(epoch));
}

void MainWindow::changeValueOfSlider4()
{
    groups = ui->horizontalSlider_4->value();
    ui->label_25->setText(QString::number(groups));
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->trainLayoutWidget->hide();
    ui->trainLayoutWidget->show();
    ui->accuracy->setText("0");
    ui->fmeasure->setText("0");
    ui->recall->setText("0");
    ui->time->setText("0");
    ui->precision->setText("0");
    ui->trainLayoutWidget->hide();
    IsClickedCommandButton = false;
}


void MainWindow::on_pushButton_4_clicked()
{
    bool is_int = true;
    auto csvFile = QFileDialog::getOpenFileName(this, tr("Open File"), "/path/to/file/", tr("Text File (*.txt)"));
    //QMessageBox::information(0,"info",csvFile);
    QFile file(csvFile);
    //std::string  line;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
       {
           QMessageBox::information(0,"error",file.errorString());
           return;
       }
    QTextStream out(&file);
     QString line = out.readLine();
     list = line.split(" ");
     //QMessageBox::information(0,"info",list[0]);
     for (int i = 0; i<list.length();i++)
     {
         list[i].toInt(&is_int);
         if (!is_int)
         {
             QMessageBox::information(0,"error","Not number weights");
             return;
         }
     }
     file.close();
}


void MainWindow::on_pushButton_5_clicked()
{
    auto download_weights = QFileDialog::getSaveFileName(this, tr("Save File"), "/path/to/file/", tr("Text File (*.txt)"));
    //QMessageBox::information(0,"info",csvFile);
    QFile file(download_weights);
    //std::string  line;
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
       {
           QMessageBox::information(0,"error",file.errorString());
           return;
       }
    QTextStream out(&file);
    for (int i = 0; i<list.length(); i++)
    {
        out<<list[i];
        if (i<list.length()-1)
            out<<' ';
    }
    file.close();

}


void MainWindow::on_radioButtonMatrix_clicked()
{
    is_matrix = ui->radioButtonMatrix->isChecked();
}


void MainWindow::on_radioButtonGraph_clicked()
{
    is_matrix = ui->radioButtonMatrix->isChecked();
}


void MainWindow::on_pushButton_2_clicked()
{

}


void MainWindow::on_uploadFileButton_clicked()
{
    bool is_int = true;
    auto csvFile = QFileDialog::getOpenFileName(this, tr("Open File"), "/path/to/file/", tr("Text File (*.txt)"));
    //QMessageBox::information(0,"info",csvFile);
    QFile file(csvFile);
    //std::string  line;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
       {
           QMessageBox::information(0,"error",file.errorString());
           return;
       }
    QTextStream out(&file);
     QString line = out.readLine();
     list = line.split(" ");
     //QMessageBox::information(0,"info",list[0]);
     for (int i = 0; i<list.length();i++)
     {
         list[i].toInt(&is_int);
         if (!is_int)
         {
             QMessageBox::information(0,"error","Not numbers in csv");
             return;
         }
     }
     file.close();
}


void MainWindow::on_runButton_clicked()
{

}

