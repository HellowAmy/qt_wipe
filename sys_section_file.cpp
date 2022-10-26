#include "sys_section_file.h"

#include "qt_show.h"

sys_section_file::sys_section_file(QObject *parent) : QObject(parent)
{

}

QVector<QString> sys_section_file::get_browser_info(QString path)
{
    QVector<QString> vec;
    QFile file(path);

    if(file.open(QIODevice::ReadOnly))
    {
        //获取文件头部信息
        QString name = file.readLine();
        vec.push_back(name);

        //获取移除路径
        while(file.atEnd() == false)
        {
            QString temp = file.readLine();
            temp = temp.section(flg(),2,2);
            temp = files_info::get_host_path() + temp;
            vec.push_back(temp);
        }

        file.close();
    }

    return vec;
}

QVector<QString> sys_section_file::get_file_path(QString path)
{
    QVector<QString> vec;
    QFile file(path);

    if(file.open(QIODevice::ReadOnly))
    {
        file.readLine();

        //获取浏览器文件路径
        while(file.atEnd() == false)
        {
            QString temp = file.readLine();
            temp = temp.section(flg(),2,2);
            temp = files_info::get_host_path() + temp;
            vec.push_back(temp);
        }

        file.close();
    }

    return vec;
}

QString sys_section_file::get_file_head(QString path)
{
    QString name;

    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        name = file.readLine();//获取文件头部信息
        name = name.section(flg(),1,1);
        name = name.section(flg_head(),1,1);

        file.close();
    }

    return name;
}

inline QString sys_section_file::flg()
{
    return "##";
}

QString sys_section_file::flg_head()
{
    return ":";
}
