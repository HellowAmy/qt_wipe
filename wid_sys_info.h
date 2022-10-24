#ifndef WID_SYS_INFO_H
#define WID_SYS_INFO_H

#include <QWidget>
#include <QPainter>

#include "qt_frameless.h"

//! 说明:
//! 该类主要作为界面承载信息
//!
class wid_sys_info : public qt_frameless
{
    Q_OBJECT
public:
    explicit wid_sys_info(QWidget *parent = nullptr);

signals:

protected:

};

#endif // WID_SYS_INFO_H
