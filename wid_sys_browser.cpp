#include "wid_sys_browser.h"

wid_sys_browser::wid_sys_browser(QWidget *parent) : qt_frameless(parent)
{
    int space = 5;
    butt_clear = new QPushButton(this);
    butt_clear->resize(250,30);
    butt_clear->move(40,20);
    butt_clear->setText("清除上网痕迹");
    butt_clear->show();

    //设置按钮透明背景（需要自定义添加背景）
    QColor col(50,50,50,127);
    QPalette palette_butt;//QPalette::Base
    palette_butt.setColor(QPalette::Button,col);

    butt_clear->setFlat(true);
    butt_clear->setAutoFillBackground(true);
    butt_clear->setPalette(palette_butt);

    //显示粉碎路径文件名列表
    tab_list = new wid_tab_list(this);
    tab_list->show();
    tab_list->move(butt_clear->pos() +
                   QPoint(0,butt_clear->height() + space));
    tab_list->open_choose();
    tab_list->set_title("文件名");
//    tab_list->add_content(ve);
    tab_list->set_size(250,200);
    tab_list->open();
}
