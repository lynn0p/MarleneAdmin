// main.cpp Copyright 2013 Owen Lynn <owen.lynn@gmail.com>
// Released under the GNU Public License V3

#include "mainwindow.h"
#include "uicardbroker.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UICardBroker broker;
    AdminMainWindow w;
    w.SetUIBroker(&broker);
    w.show();
    
    return a.exec();
}
