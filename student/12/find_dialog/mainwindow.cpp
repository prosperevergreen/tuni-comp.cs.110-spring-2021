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
    connect(ui->findPushButton,&QPushButton::clicked, this, &MainWindow::findPushButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::findPushButton()
{
    Qt::CaseSensitivity caseSense = ui->matchCheckBox->isChecked() ?  Qt::CaseSensitive : Qt::CaseInsensitive;
    QString fileName = ui->fileLineEdit->text();
    ui->fileLineEdit->setText("");
    QString searchTerm = ui->keyLineEdit->text();
    ui->keyLineEdit->setText("");

    // Search for file
    QFile file(fileName);
    if (fileName.isEmpty() || !file.open(QIODevice::ReadOnly | QIODevice::Text)){
         ui->textBrowser->setText(NO_FILE);
         return;
    }

    // Check if search word exists
    if(searchTerm.isEmpty()){
        ui->textBrowser->setText(YES_FILE);
        return;
    }

    // Search for word
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();

        if(line.contains(searchTerm, caseSense)){
            ui->textBrowser->setText(YES_WORD);
            return;
        }
    }

    // Word not found
    ui->textBrowser->setText(NO_WORD);
}
