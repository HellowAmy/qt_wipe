#ifndef WID_SYS_BROWSER_H
#define WID_SYS_BROWSER_H

#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QPushButton>

#include "qt_frameless.h"
#include "wid_tab_list.h"
#include "files_info.h"
#include "sys_section_file.h"
#include "qt_wipe.h"
#include "qt_dialog.h"

//! 说明:
//! 该类用于承载清除上网痕迹的界面
//! 提供清除按钮
//!
class wid_sys_browser : public qt_frameless
{
    Q_OBJECT
public:
    explicit wid_sys_browser(QWidget *parent = nullptr);
    void scan_browser();

signals:
    emit void fa_scan_browser();
    emit void fa_clear_failed();

protected:
    wid_tab_list *tab_list;
    qt_dialog *dialog_clear;
    qt_dialog *dialog_failed;

    QPushButton *butt_clear;//清空浏览器痕迹
    QStringList list_conf;//配置文件路径

    bool clear_browser();
    void add_list_info();

};

#endif // WID_SYS_BROWSER_H
