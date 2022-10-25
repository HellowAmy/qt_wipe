#include "files_info.h"

files_info::files_info(QObject *parent) : QObject(parent)
{

}

QStringList files_info::get_files_name(QString path)
{
    QStringList list;

    QFileInfoList list_info = get_files_info(path);
    for(int i=0;i<list_info.size();i++)
    {
        QFileInfo info(list_info[i]);
        list<<info.absoluteFilePath();
    }

    return list;
}

QFileInfoList files_info::get_files_info(QString path)
{
    QDir dir(path);
    QFileInfoList list_file = dir.entryInfoList
            (QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList list_dir = dir.entryInfoList
            (QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i != list_dir.size(); i++)
    {
         QString name = list_dir.at(i).absoluteFilePath();
         QFileInfoList child_file_list = get_files_info(name);
         list_file.append(child_file_list);
    }

    return list_file;
}

QString files_info::get_host_path()
{
    QString str;
    str += QStandardPaths::writableLocation
            (QStandardPaths::HomeLocation);
    str += "/";
    return str;
}
