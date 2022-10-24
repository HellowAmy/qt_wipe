#ifndef WID_SYS_WIPE_H
#define WID_SYS_WIPE_H

#include <QWidget>

#include <QString>
#include <QLineEdit>
#include <QPushButton>

#include "qt_frameless.h"
#include "wid_tab_list.h"

//! 说明:
//! 该类用于承载粉碎文件的界面
//! 拥有展示文件信息列表
//! 两个清空按钮
//!
class wid_sys_wipe : public qt_frameless
{
    Q_OBJECT
public:
    explicit wid_sys_wipe(QWidget *parent = nullptr);

signals:

protected:
    wid_tab_list *tab_list;

    QLineEdit *edit_path;//获取粉碎文件路径
    QPushButton *butt_wipe;//粉碎文件
    QPushButton *butt_recover;//清空回收站

    QString str_edit_info;

    void init();//控件初始化
    void signal();//启动信号槽

};

#endif // WID_SYS_WIPE_H
