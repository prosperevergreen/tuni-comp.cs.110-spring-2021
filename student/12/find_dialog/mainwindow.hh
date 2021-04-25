#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const QString NO_FILE = "File not found";
const QString YES_FILE = "File found";
const QString NO_WORD = "Word not found";
const QString YES_WORD = "Word found";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonFind_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HH
