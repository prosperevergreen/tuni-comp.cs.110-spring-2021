#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sec_(0)
    , min_(0)
{
    ui->setupUi(this);

    ui->lcdNumberMin->setStyleSheet("background-color: blue; color:white;");
    ui->lcdNumberSec->setStyleSheet("background-color: pink; color:black;");
    setTimer();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::runTimer);
}

void MainWindow::runTimer()
{
    // Increase the seconds
    sec_++;
    // If seconds is == 60, reset secs
    if (sec_ == 60) {

        min_++;
        sec_ = 0;

        // Check if mins equal 60
        if (min_ == 60) {
            min_ = 0;
        }
    }
    // update timer
    setTimer();
}

void MainWindow::setTimer()
{
    ui->lcdNumberMin->display(min_);
    ui->lcdNumberSec->display(sec_);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    if (timer->isActive())
        return;
    timer->start(SEC);
}

void MainWindow::on_stopButton_clicked()
{
    if (!timer->isActive())
        return;
    timer->stop();
}

void MainWindow::on_resetButton_clicked()
{
    min_ = 0;
    sec_ = 0;
    setTimer();
}
