#ifndef SYS_INFO_H
#define SYS_INFO_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QNetworkAddressEntry>
#include <QNetworkInterface>
#include <QMap>

#include <iostream>
#include <fstream>
#include <string>

#include "files_info.h"

using std::fstream;
using std::string;
using std::cout;
using std::endl;
using std::getline;
using std::ios;

class sys_info : public QObject
{
    Q_OBJECT
public:
    explicit sys_info(QObject *parent = nullptr);

    virtual QString get_sys_version() = 0;
    virtual QString get_sys_cpu() = 0;
    virtual QString get_sys_mem() = 0;
    virtual QString get_host() = 0;
    virtual QString get_ip_net() = 0;

    QString flg();
signals:

protected:

};

class sys_info_klin : public sys_info
{
    Q_OBJECT
public:
    explicit sys_info_klin(QObject *parent = nullptr);

    QString get_sys_version() override;
    QString get_sys_cpu() override;
    QString get_sys_mem() override;
    QString get_host() override;
    QString get_ip_net() override;

signals:

protected:


};



#endif // SYS_INFO_H
