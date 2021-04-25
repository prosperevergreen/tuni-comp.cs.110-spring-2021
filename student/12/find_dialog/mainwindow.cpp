#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonFind_clicked()
{
    Qt::CaseSensitivity caseSense = ui->checkBoxMatchCap->isChecked() ?  Qt::CaseSensitive : Qt::CaseInsensitive;
    QString fileName = ui->lineEditFileName->text();
    ui->lineEditFileName->setText("");
    QString searchTerm = ui->lineEditSearchTerm->text();
    ui->lineEditSearchTerm->setText("");

    // Search for file
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
         ui->textBrowserResult->setText(NO_FILE);
         return;
    }

    // Check if search word exists
    if(searchTerm.isEmpty()){
        ui->textBrowserResult->setText(YES_FILE);
        return;
    }

    // Search for word
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();

        if(line.contains(searchTerm, caseSense)){
            ui->textBrowserResult->setText(YES_WORD);
            return;
        }
    }

    // Word not found
    ui->textBrowserResult->setText(NO_WORD);
}
