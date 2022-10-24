#ifndef WID_SYS_BROWSER_H
#define WID_SYS_BROWSER_H

#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QPushButton>

#include "qt_frameless.h"
#include "wid_tab_list.h"

//! 说明:
//! 该类用于承载清除上网痕迹的界面
//! 提供清除按钮
//!
class wid_sys_browser : public qt_frameless
{
    Q_OBJECT
public:
    explicit wid_sys_browser(QWidget *parent = nullptr);

signals:

protected:
    wid_tab_list *tab_list;
    QPushButton *butt_clear;//清空浏览器痕迹

};

#endif // WID_SYS_BROWSER_H
