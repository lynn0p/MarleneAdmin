// uicardbroker.h Copyright 2013 Owen Lynn <owen.lynn@gmail.com>
// Released under the GNU Public License V3

#ifndef UICARDBROKER_H
#define UICARDBROKER_H
#include <QtCore>

class SmartCardMarlene;

class UICardBroker
{
public:
    UICardBroker();
    virtual ~UICardBroker();

    int SetNewPassphrase(const QString &oldpass, const QString &newpass);
    int SetNewPIN(const QString &curpass, const QString &newpin);
    int SetContactInfo(const QString &curpass, const QString &contact_info);
    int SetHostData(const QString &curpass, const QString &hostname, const QString &portstr);
    int SetWalletPassphrase(const QString &curpass, const QString &walletpass);
    int Nuke();
    int GetContactInfo(QString &out);
    int GetHostData(QString &host_out, QString &port_out);
    int SetPublicKey(const QString &curpass, const QString &pemfile);

private:
    // do not impl
    UICardBroker(const UICardBroker &src);
    UICardBroker &operator= (const UICardBroker & src);

    bool ReadZCPublicKey(const std::string & filename, std::string &zcpkey);
    bool PokeZCPublicKey(const std::string &passhash, SmartCardMarlene &card, const std::string &zcpkey);
};

#endif // UICARDBROKER_H
