// uicardbroker.cpp Copyright 2013 Owen Lynn <owen.lynn@gmail.com>
// Released under the GNU Public License V3

#include "uicardbroker.h"
#include "SmartCardMarlene.h"
#include "Util.h"
#include <fstream>
#include <QtCore>

#define SUCCESS                                        0x00000000

#define ERROR_UNKNOWN                                  0x80000000
#define ERROR_CARD_INIT_FAIL                           0x80000001
#define ERROR_CARD_WAITCONNECT_FAIL                    0x80000002
#define ERROR_CARD_TERM_FAIL                           0x80000003
#define ERROR_CARD_SETNEWPASSPHRASE_FAIL               0x80000004
#define ERROR_CARD_SETNEWPIN_FAIL                      0x80000005
#define ERROR_CARD_SETCONTACTINFO_FAIL                 0x80000006
#define ERROR_CARD_SETHOSTDATA_FAIL                    0x80000007
#define ERROR_CARD_SETWALLETPASSPHRASE_FAIL            0x80000008
#define ERROR_CARD_NUKE_FAIL                           0x80000009
#define ERROR_GETCONTACTINFO_FAIL                      0x8000000a
#define ERROR_CARD_GETHOSTDATA_FAIL                    0x8000000b
#define ERROR_CARD_READZCPUBLICKEY_FAIL                0x8000000c
#define ERROR_CARD_POKEZCPUBLICKEY_FAIL                0x8000000d

UICardBroker::UICardBroker()
{
}

UICardBroker::~UICardBroker()
{
}

int
UICardBroker::SetNewPassphrase(const QString &oldpass, const QString &newpass)
{
    int rc = ERROR_UNKNOWN;
    std::string stl_oldpass,stl_newpass,oldhash,newhash;
    SmartCardMarlene card;
    if (!card.Init()) {
        rc = ERROR_CARD_INIT_FAIL;
        goto error;
    }
    if (!card.WaitConnect()) {
        rc = ERROR_CARD_WAITCONNECT_FAIL;
        goto error;
    }
    stl_oldpass = oldpass.toStdString();
    stl_newpass = newpass.toStdString();
    oldhash = Utility::Sha256Hash(stl_oldpass);
    newhash = Utility::Sha256Hash(stl_newpass);
    if (!card.SetNewPassphrase(oldhash,newhash)) {
        rc = ERROR_CARD_SETNEWPASSPHRASE_FAIL;
        goto error;
    }
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return SUCCESS;

error:
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return rc;
}

int
UICardBroker::SetNewPIN(const QString &curpass, const QString &newpin)
{
    int rc = ERROR_UNKNOWN;
    std::string stl_curpass,stl_newpin,passhash;
    SmartCardMarlene card;
    if (!card.Init()) {
        rc = ERROR_CARD_INIT_FAIL;
        goto error;
    }
    if (!card.WaitConnect()) {
        rc = ERROR_CARD_WAITCONNECT_FAIL;
        goto error;
    }
    stl_curpass = curpass.toStdString();
    stl_newpin = newpin.toStdString();
    passhash = Utility::Sha256Hash(stl_curpass);
    if (!card.SetNewPIN(passhash,stl_newpin)) {
        rc = ERROR_CARD_SETNEWPIN_FAIL;
        goto error;
    }
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return SUCCESS;

error:
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return rc;
}

int
UICardBroker::SetContactInfo(const QString &curpass, const QString &contact_info)
{
    int rc = ERROR_UNKNOWN;
    std::string stl_curpass,passhash,stl_contact_info;
    SmartCardMarlene card;
    if (!card.Init()) {
        rc = ERROR_CARD_INIT_FAIL;
        goto error;
    }
    if (!card.WaitConnect()) {
        rc = ERROR_CARD_WAITCONNECT_FAIL;
        goto error;
    }
    stl_curpass = curpass.toStdString();
    stl_contact_info = contact_info.toStdString();
    passhash = Utility::Sha256Hash(stl_curpass);
    if (!card.SetContactInfo(passhash,stl_contact_info)) {
        rc = ERROR_CARD_SETCONTACTINFO_FAIL;
        goto error;
    }
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return SUCCESS;

error:
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return rc;
}

int
UICardBroker::SetHostData(const QString &curpass, const QString &hostname, const QString &portstr)
{
    int rc = ERROR_UNKNOWN;
    unsigned long port;
    std::string stl_curpass,stl_hostname,passhash;
    SmartCardMarlene card;
    if (!card.Init()) {
        rc = ERROR_CARD_INIT_FAIL;
        goto error;
    }
    if (!card.WaitConnect()) {
        rc = ERROR_CARD_WAITCONNECT_FAIL;
        goto error;
    }
    stl_curpass = curpass.toStdString();
    stl_hostname = hostname.toStdString();
    port = portstr.toULong();
    passhash = Utility::Sha256Hash(stl_curpass);
    if (!card.SetHostData(passhash,port,stl_hostname)) {
        rc = ERROR_CARD_SETHOSTDATA_FAIL;
        goto error;
    }
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return SUCCESS;

error:
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return rc;
}

int
UICardBroker::SetWalletPassphrase(const QString &curpass, const QString &walletpass)
{
    int rc = ERROR_UNKNOWN;
    std::string stl_curpass,stl_walletpass,passhash;
    SmartCardMarlene card;
    if (!card.Init()) {
        rc = ERROR_CARD_INIT_FAIL;
        goto error;
    }
    if (!card.WaitConnect()) {
        rc = ERROR_CARD_WAITCONNECT_FAIL;
        goto error;
    }
    stl_curpass = curpass.toStdString();
    stl_walletpass = walletpass.toStdString();
    passhash = Utility::Sha256Hash(stl_curpass);
    if (!card.SetWalletPassphrase(passhash,stl_walletpass)) {
        rc = ERROR_CARD_SETWALLETPASSPHRASE_FAIL;
        goto error;
    }
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return SUCCESS;

error:
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return rc;
}

int
UICardBroker::Nuke()
{
    int rc = ERROR_UNKNOWN;
    SmartCardMarlene card;
    if (!card.Init()) {
        rc = ERROR_CARD_INIT_FAIL;
        goto error;
    }
    if (!card.WaitConnect()) {
        rc = ERROR_CARD_WAITCONNECT_FAIL;
        goto error;
    }
    if (!card.Nuke()) {
        rc = ERROR_CARD_NUKE_FAIL;
        goto error;
    }
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return SUCCESS;

error:
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return rc;
}

int
UICardBroker::GetContactInfo(QString &out)
{
    int rc = ERROR_UNKNOWN;
    std::string stl_contact_info;
    QByteArray contact_info;
    SmartCardMarlene card;
    if (!card.Init()) {
        rc = ERROR_CARD_INIT_FAIL;
        goto error;
    }
    if (!card.WaitConnect()) {
        rc = ERROR_CARD_WAITCONNECT_FAIL;
        goto error;
    }
    if (!card.GetContactInfo(stl_contact_info)) {
        rc = ERROR_GETCONTACTINFO_FAIL;
        goto error;
    }
    contact_info.clear();
    contact_info.append(stl_contact_info.c_str(),stl_contact_info.length());
    out = contact_info;
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return SUCCESS;

error:
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return rc;
}

int
UICardBroker::GetHostData(QString &host_out, QString &port_out)
{
    int rc = ERROR_UNKNOWN;
    std::string stl_host;
    unsigned long port;
    QByteArray portstr,host;
    SmartCardMarlene card;
    if (!card.Init()) {
        rc = ERROR_CARD_INIT_FAIL;
        goto error;
    }
    if (!card.WaitConnect()) {
        rc = ERROR_CARD_WAITCONNECT_FAIL;
        goto error;
    }
    if (!card.GetHostData(port,stl_host)) {
        rc = ERROR_CARD_GETHOSTDATA_FAIL;
        goto error;
    }
    portstr = QByteArray::number((uint)port);
    host.clear();
    host.append(stl_host.c_str(),stl_host.length());
    port_out = portstr;
    host_out = host;
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return SUCCESS;

error:
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return rc;
}

int
UICardBroker::SetPublicKey(const QString &curpass, const QString &pemfile)
{
    int rc = ERROR_UNKNOWN;
    std::string stl_curpass,passhash,stl_pemfile,zcpkey;
    SmartCardMarlene card;
    if (!card.Init()) {
        rc = ERROR_CARD_INIT_FAIL;
        goto error;
    }
    if (!card.WaitConnect()) {
        rc = ERROR_CARD_WAITCONNECT_FAIL;
        goto error;
    }
    stl_curpass = curpass.toStdString();
    stl_pemfile = pemfile.toStdString();
    passhash = Utility::Sha256Hash(stl_curpass);

    if (!ReadZCPublicKey(stl_pemfile,zcpkey)) {
        rc = ERROR_CARD_READZCPUBLICKEY_FAIL;
        goto error;
    }
    if (!PokeZCPublicKey(passhash,card,zcpkey)) {
        rc = ERROR_CARD_POKEZCPUBLICKEY_FAIL;
        goto error;
    }
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return SUCCESS;

error:
    if (!card.Term()) { return ERROR_CARD_TERM_FAIL; }
    return rc;
}

bool
UICardBroker::ReadZCPublicKey(const std::string & filename, std::string &zcpkey)
{
    std::string filebuf;
    std::ifstream file(filename);
    if (file.good()) {
        while (!file.eof()) {
            int c = file.get();
            if (c != EOF) {
                filebuf += (char)c;
            }
        }
    } else {
        return false;
    }
    if (filebuf.length() > 0) {
        int pos1 = filebuf.find("-----BEGIN PUBLIC KEY-----");
        pos1 += sizeof("-----BEGIN PUBLIC KEY-----");
        int pos2 = filebuf.rfind("-----END PUBLIC KEY-----");
        std::string base64buf = filebuf.substr(pos1,pos2-pos1);
        std::string ossl_pkey = Utility::Base64Decode(base64buf);
        zcpkey = Utility::OSSLPublicKey2ZCPublicKey(ossl_pkey);
    } else {
        return false;
    }
    return true;
}

bool
UICardBroker::PokeZCPublicKey(const std::string &passhash, SmartCardMarlene &card, const std::string &zcpkey)
{
    bool rc=false;
    bool append=false;
    unsigned int i=0;
    while (i < zcpkey.length()) {
        std::string chunk;
        chunk = zcpkey.substr(i,SmartCardMarlene::SAFE_CHUNK_LENGTH);
        rc = card.SetPublicKeyData(passhash,append,chunk);
        if (!rc) { break; }
        append = true;
        i += chunk.length();
    }
    return rc;
}
