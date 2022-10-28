#ifndef WID_MAIN_H
#define WID_MAIN_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

#include "wid_sys_info.h"
#include "qt_frameless.h"
#include "wid_list_butt.h"
#include "wid_sys_wipe.h"
#include "wid_sys_browser.h"
#include "qt_manage.h"
#include "qt_butt.h"

class wid_main : public qt_frameless
{
    Q_OBJECT
public:
    explicit wid_main(QWidget *parent = nullptr);

signals:
    emit void fa_press_right();

protected:
    wid_sys_info *sys_info;
    wid_sys_wipe *sys_wipe;
    wid_sys_browser *sys_browser;

    wid_list_butt *list_butt;
    qt_manage *manage_move;


    void mousePressEvent(QMouseEvent *event) override;

};

#endif // WID_MAIN_H
