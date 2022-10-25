#ifndef FILES_INFO_H
#define FILES_INFO_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfoList>

class files_info : public QObject
{
    Q_OBJECT
public:
    explicit files_info(QObject *parent = nullptr);
    static QStringList get_files_name(QString path);//获取路径下文件绝对路径
    static QFileInfoList get_files_info(QString path);//获取路径下文件信息
    static QString get_host_path();//获取根路径

signals:

};

#endif // FILES_INFO_H
