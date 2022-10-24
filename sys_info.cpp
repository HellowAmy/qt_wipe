#include "sys_info.h"

sys_info::sys_info(QObject *parent) : QObject(parent)
{

}

QString sys_info::flg()
{
    return "##";
}

sys_info_klin::sys_info_klin(QObject *parent)
{

}

QString sys_info_klin::get_sys_version()
{
    QString str;
    QString str_kernel;
    QString str_version;

    //统一使用fstream，QFile类不可用，打开/proc路径下文件出错
    fstream ofs("/proc/version",ios::in);
    if(ofs.is_open())
    {
        string buf;
        while(getline(ofs,buf))
        {
            str = QString::fromStdString(buf);
        }

        //多余字符切割
        str_kernel = str.section("-",0,0);
        str_kernel = str_kernel.section(" ",0,0)
                        +" "+ str_kernel.section(" ",2,2);
        str_version = str.section(" ",2,2);
        str_version = str_version.section(".",3,-1);

        str = str_kernel + flg() + str_version;
    }

    return str;
}

QString sys_info_klin::get_sys_cpu()
{
    QString str;
    QString str_type;
    QString str_size;

    //统一使用fstream，QFile类不可用，打开/proc路径下文件出错
    fstream ofs("/proc/cpuinfo",ios::in);
    if(ofs.is_open())
    {
        bool is_null = true;
        int count = 0;

        string buf;
        while(getline(ofs,buf))
        {
            //统计核心
            if(buf.find("physical id") != string::npos) count++;

            //检索芯片类型
            if(is_null && buf.find("model name") != string::npos)
            {
                is_null = false;
                str_type = QString::fromStdString(buf);
            }
        }
        str_size = QString::number(count);

        //多余字符切割
        str_type = str_type.section(" ",2,-1);
        str_type = str_type.section(" ",0,3)
                    + " " + str_type.section(" ",6,6);

        str = str_type + this->flg() + str_size;
    }

    return str;
}

QString sys_info_klin::get_sys_mem()
{
    QString str;
    QString str_all;
    QString str_free;

    //统一使用fstream，QFile类不可用，打开/proc路径下文件出错
    fstream ofs("/proc/meminfo",ios::in);
    if(ofs.is_open())
    {
        int count = 0;

        string buf;
        while(getline(ofs,buf))
        {
            //内存总量
            if(buf.find("MemTotal") != string::npos)
            {
                str_all = QString::fromStdString(buf);
                count++;
            }

            //内存剩余
            if(buf.find("MemFree") != string::npos)
            {
                str_free = QString::fromStdString(buf);
                count++;
            }

            if(count == 2) break;
        }

        //多余字符切割
        str_all = QString::number(str_all.section(" ",-2,-2).toInt() / 1024);
        str_free = QString::number(str_free.section(" ",-2,-2).toInt() / 1024);

        str = str_all + flg() + str_free;
    }

    return str;
}

QString sys_info_klin::get_host()
{
    QString str;
    QString str_host;
    QString str_user;

    //统一使用fstream，QFile类不可用，打开/proc路径下文件出错
    fstream ofs("/etc/hostname",ios::in);
    if(ofs.is_open())
    {
        string buf;
        while(getline(ofs,buf))
        {
            str_host = QString::fromStdString(buf);
        }

        str_user = files_info::get_host_path();
        str_user = str_user.section("/",-2,-2);

        str =  str_host + flg() + str_user;
    }

    return str;
}

QString sys_info_klin::get_ip_net()
{
    QString str;
    QMap<QString,QString> map;

    QList<QNetworkInterface> list_face = QNetworkInterface::allInterfaces();
    for(auto it = list_face.begin();it != list_face.end();it++)
    {
        QNetworkInterface interf = *it;
        QString inter = interf.humanReadableName(); //接口名称（网卡）

        //获取网卡内数据列表--读取一个IP地址列表
        QList<QNetworkAddressEntry> list_entry = interf.addressEntries();
        for(auto it = list_entry.begin();it != list_entry.end();it++)
        {
            QString ip;
            QString mask;
            QHostAddress addr = it->ip();

            //排除多余网络地址
            if(addr.protocol() == QAbstractSocket::IPv4Protocol
                    && addr != QHostAddress::LocalHost)
            {
                ip = addr.toString();//地址转文本
                mask = it->netmask().toString();//子网掩码
                QString temp = ip +flg()+ mask;
                map.insert(inter,temp);
            }
        }
    }

    //获取指定的网卡，失败则随机获取
    auto it = map.find("ens33");
    if(it != map.end()) str = it.value();
    else if(map.size() > 0) str = *map.begin();

    return str;
}
