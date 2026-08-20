#include "mainwindow.h"
#include "./ui_mainwindow.h"


void PrintProcess(){


}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    layout = new QVBoxLayout();
    table = new QTableView(this);
    model = new QStandardItemModel(0,3,this);


    layout->addWidget(table);
    ui->centralwidget->setLayout(layout);
    model->setHorizontalHeaderLabels({"Процесы","ID","Потоки"});
    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

    if(snapshot == INVALID_HANDLE_VALUE){
        qDebug() << "Error: " << GetLastError();
        return;
    }

    pe.dwSize = sizeof(PROCESSENTRY32W);
    if(Process32FirstW(snapshot,&pe)){
        do{
            QString procName = QString::fromWCharArray(pe.szExeFile);
            QString procId   = QString::number(pe.th32ProcessID);
            QString threads  = QString::number(pe.cntThreads);

            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(procName)
                     << new QStandardItem(procId)
                     << new QStandardItem(threads);
            for (QStandardItem* item : rowItems) {
                item->setEditable(false);
            }

            model->appendRow(rowItems);
        }while(Process32NextW(snapshot, &pe));
    }
    CloseHandle(snapshot);
    table->setModel(model);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    table->show();
}



MainWindow::~MainWindow()
{
    delete ui;
}
