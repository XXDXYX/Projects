#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <windows.h>
#include <QDebug>
#include <TlHelp32.h>
#include <QThread>
#include <QMutex>
#include <QHeaderView>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE





class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTableView *table;
    QStandardItemModel *model;
    QVBoxLayout *layout;
    HANDLE snapshot;
    PROCESSENTRY32W pe;
};
#endif // MAINWINDOW_H
