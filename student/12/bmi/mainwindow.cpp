#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include  <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->countButton, &QPushButton::clicked, this, &MainWindow::calcBMI);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calcBMI(){


    QString weightText = ui->weightLineEdit->text();
    QString heightText = ui->heightLineEdit->text();
    // a digit (\d), zero or more times (*)
    QRegExp re("\\d*");

    // Check if values are invalid
    if(!re.exactMatch(weightText) || !re.exactMatch(heightText))
        return;

    // Try conversion of QString to int
    float weight = weightText.toFloat();
    float height = heightText.toFloat()/100;



    // Calculate height square
    float heightSqr = height * height;

    // Calculate bmi
    float bmi = weight / heightSqr;


    ui->resultLabel->setText(QString::number(bmi));

    // Optionally display BMI class
    if(bmi < 15){
        ui->infoTextBrowser->setText(UNDER_WEIGHT);
        return;
    }

    if(bmi > 25){
        ui->infoTextBrowser->setText(OVER_WEIGHT);
        return;
    }

    ui->infoTextBrowser->setText(OK_WEIGHT);

}

