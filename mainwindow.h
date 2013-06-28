// mainwindow.h Copyright 2013 Owen Lynn <owen.lynn@gmail.com>
// Released under the GNU Public License V3

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "uicardbroker.h"

namespace Ui {
class AdminMainWindow;
}

class AdminMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit AdminMainWindow(QWidget *parent = 0);
    ~AdminMainWindow();

    void SetUIBroker(UICardBroker *broker);

public slots:
    void onSetNewPassphrase();
    void onSetNewPIN();
    void onSetContactInfo();
    void onSetHostData();
    void onSetWalletPassphrase();
    void onSetFactoryDefaults();
    void onSetPublicKey();
    void onQueryCard();
    
private:
    Ui::AdminMainWindow *m_ui;
    UICardBroker        *m_broker;
};

#endif // MAINWINDOW_H
