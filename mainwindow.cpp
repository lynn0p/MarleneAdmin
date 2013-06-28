// mainwindow.cpp Copyright 2013 Owen Lynn <owen.lynn@gmail.com>
// Released under the GNU Public License V3

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QFileDialog>

AdminMainWindow::AdminMainWindow(QWidget *parent) :
    QMainWindow(parent), m_ui(new Ui::AdminMainWindow)
{
    m_ui->setupUi(this);
}

AdminMainWindow::~AdminMainWindow()
{
    delete m_ui;
}

void
AdminMainWindow::SetUIBroker(UICardBroker *broker)
{
    m_broker = broker;
}

void
AdminMainWindow::onSetNewPassphrase()
{
    QString curpass = m_ui->cur_passphrase_edit->text();
    QString newpass = m_ui->new_passphrase_edit->text();
    int rc = m_broker->SetNewPassphrase(curpass,newpass);
    if (rc < 0) {
        QString fail_msg;
        fail_msg += "Failure code = ";
        fail_msg += "0x" + QByteArray::number(rc,16);
        QMessageBox::critical(this,"Set New Passphrase", fail_msg);
    } else {
        QMessageBox::information(this,"Set New Passphrase", "Success!");
    }
}

void
AdminMainWindow::onSetNewPIN()
{
    QString curpass = m_ui->cur_passphrase_edit->text();
    QString newpin = m_ui->new_pin_edit->text();
    int rc = m_broker->SetNewPIN(curpass,newpin);
    if (rc < 0) {
        QString fail_msg;
        fail_msg += "Failure code = ";
        fail_msg += "0x" + QByteArray::number(rc,16);
        QMessageBox::critical(this,"Set New PIN", fail_msg);
    } else {
        QMessageBox::information(this,"Set New PIN", "Success!");
    }
}

void
AdminMainWindow::onSetContactInfo()
{
    QString curpass = m_ui->cur_passphrase_edit->text();
    QString contact_info = m_ui->contact_info_edit->text();
    int rc = m_broker->SetContactInfo(curpass,contact_info);
    if (rc < 0) {
        QString fail_msg;
        fail_msg += "Failure code = ";
        fail_msg += "0x" + QByteArray::number(rc,16);
        QMessageBox::critical(this,"Set Contact Info", fail_msg);
    } else {
        QMessageBox::information(this,"Set Contact Info", "Success!");
    }
}

void
AdminMainWindow::onSetHostData()
{
    QString curpass = m_ui->cur_passphrase_edit->text();
    QString hostname = m_ui->host_edit->text();
    QString portstr = m_ui->port_edit->text();
    int rc = m_broker->SetHostData(curpass,hostname,portstr);
    if (rc < 0) {
        QString fail_msg;
        fail_msg += "Failure code = ";
        fail_msg += "0x" + QByteArray::number(rc,16);
        QMessageBox::critical(this,"Set Host Data", fail_msg);
    } else {
        QMessageBox::information(this,"Set Host Data", "Success!");
    }
}

void
AdminMainWindow::onSetWalletPassphrase()
{
    QString curpass = m_ui->cur_passphrase_edit->text();
    QString walletpass = m_ui->wallet_pass_edit->text();
    int rc = m_broker->SetWalletPassphrase(curpass,walletpass);
    if (rc < 0) {
        QString fail_msg;
        fail_msg += "Failure code = ";
        fail_msg += "0x" + QByteArray::number(rc,16);
        QMessageBox::critical(this,"Set Host Data", fail_msg);
    } else {
        QMessageBox::information(this,"Set Host Data", "Success!");
    }
}

void
AdminMainWindow::onSetFactoryDefaults()
{
    int rc = m_broker->Nuke();
    if (rc < 0) {
        QString fail_msg;
        fail_msg += "Failure code = ";
        fail_msg += "0x" + QByteArray::number(rc,16);
        QMessageBox::critical(this,"Set Factory Defaults", fail_msg);
    } else {
        QMessageBox::information(this,"Set Factory Defaults", "Success!");
    }
}

void
AdminMainWindow::onSetPublicKey()
{
    QString pemfile = QFileDialog::getOpenFileName(this,"Select a public key file", "", "PEM Files (*.pem)");
    if (pemfile == "") {
        QMessageBox::critical(this,"Set Public Key", "No file selected!");
        return;
    }
    QString curpass = m_ui->cur_passphrase_edit->text();
    int rc = m_broker->SetPublicKey(curpass,pemfile);
    if (rc < 0) {
        QString fail_msg;
        fail_msg += "Failure code = ";
        fail_msg += "0x" + QByteArray::number(rc,16);
        QMessageBox::critical(this,"Set Public Key", fail_msg);
    } else {
        QMessageBox::information(this,"Set Public Key", "Success!");
    }
}

void
AdminMainWindow::onQueryCard()
{
    QString contact_info;
    QString hostname;
    QString portstr;
    int rc = m_broker->GetContactInfo(contact_info);
    if (rc < 0) {
        QString fail_msg;
        fail_msg += "Failure code = ";
        fail_msg += "0x" + QByteArray::number(rc,16);
        QMessageBox::critical(this,"Query Card", fail_msg);
        return;
    }
    rc = m_broker->GetHostData(hostname,portstr);
    if (rc < 0) {
        QString fail_msg;
        fail_msg += "Failure code = ";
        fail_msg += "0x" + QByteArray::number(rc,16);
        QMessageBox::critical(this,"Query Card", fail_msg);
        return;
    }
    m_ui->contact_info_edit->setText(contact_info);
    m_ui->host_edit->setText(hostname);
    m_ui->port_edit->setText(portstr);
}
