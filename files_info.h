#ifndef FILES_INFO_H
#define FILES_INFO_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QStandardPaths>

class files_info : public QObject
{
    Q_OBJECT
public:
    explicit files_info(QObject *parent = nullptr);

    static QString get_host_path();

signals:

};

#endif // FILES_INFO_H
