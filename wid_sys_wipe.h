#ifndef WID_SYS_WIPE_H
#define WID_SYS_WIPE_H

#include <QWidget>

#include <QString>
#include <QLineEdit>
#include <QPushButton>

#include "rules/wid_rules.h"
#include "qt_frameless.h"
#include "wid_tab_list.h"
#include "files_info.h"
#include "qt_wipe.h"
#include "qt_dialog.h"

//! 说明:
//! 该类用于承载粉碎文件的界面
//! 拥有展示文件信息列表
//! 获取粉碎文件路径是通过拖入的方式
//!
class wid_sys_wipe : public qt_frameless
{
    Q_OBJECT
public:
    explicit wid_sys_wipe(QWidget *parent = nullptr);
    void clear_recover();

signals:
    emit void fa_failed_recover();

protected:
    wid_tab_list *tab_list;
    qt_dialog *dialog_wipe;
    qt_dialog *dialog_recover;
    qt_dialog *dialog_failed;
    wid_rules *v_rules;

    QLineEdit *edit_path;//获取粉碎文件路径
    QPushButton *butt_wipe;//粉碎文件
    QPushButton *butt_recover;//清空回收站
    QPushButton *butt_rules;//规则粉碎

    QStringList list_wipe;//粉碎文件路径
    QString str_edit_info;//拖动提示

    void init();//控件初始化
    void signal();//启动信号槽

    void get_path_edit(QString path);//取出拖入路径并放入列表
    void wipe_list_file();//清空打勾列表

};

#endif // WID_SYS_WIPE_H
