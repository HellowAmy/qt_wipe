#ifndef QT_WIPE_H
#define QT_WIPE_H

#include <QObject>
#include <QFileInfo>

#include <string>

#include "lib/wipe/wipeinterface.h"

//! 说明:
//! 通过前辈预留接口函数destroy_interface粉碎文件
//! wipe_path只需要文件路径，支持文件夹和文件粉碎
//!
class qt_wipe : public QObject
{
    Q_OBJECT
public:
    explicit qt_wipe(QObject *parent = nullptr);
    static bool wipe_path(QString path);

signals:

};

#endif // QT_WIPE_H
