#ifndef SYS_SECTION_FILE_H
#define SYS_SECTION_FILE_H

#include <QObject>
#include <QVector>
#include <QFile>

#include "files_info.h"

class sys_section_file : public QObject
{
    Q_OBJECT
public:
    explicit sys_section_file(QObject *parent = nullptr);
    static QVector<QString> get_browser_info(QString path);//读取浏览器文件内容
    static QVector<QString> get_file_path(QString path);//获取浏览器路径
    static QString get_file_head(QString path);//获取头部信息
    static inline QString flg();//切割标记
    static inline QString flg_head();//切割标记

signals:




};

#endif // SYS_SECTION_FILE_H
