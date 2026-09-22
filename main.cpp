#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/style.qss");
    if(qss.open(QFile::ReadOnly)){
        a.setStyleSheet(qss.readAll());
        qss.close();
    }
    MainWindow w;
    w.show();
    return QApplication::exec();
}
