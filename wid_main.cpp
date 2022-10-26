#include "wid_main.h"

#include "qt_show.h"

wid_main::wid_main(QWidget *parent) : qt_frameless(parent)
{
    this->set_back(":/pic_title.png");
////    this->set_frameless(true);
    this->set_frameless(false);

    //系统信息
    sys_info = new wid_sys_info(this);
    sys_info->set_back(":/pic_info.png");
    sys_info->resize(520,280);
    sys_info->move(150,150 / 2);
    sys_info->show();

    //文件粉碎
    sys_wipe = new wid_sys_wipe(this);
    sys_wipe->set_back(":/pic_info.png");
    sys_wipe->resize(520,280);
////    sys_info->move(150,150 / 2);
    sys_wipe->move(150,300);
    sys_wipe->show();

    //浏览器清除
    sys_browser = new wid_sys_browser(this);
    sys_browser->set_back(":/pic_info.png");
    sys_browser->resize(520,280);
    sys_browser->move(150,450);
    sys_browser->show();

    //按键容器列表
    list_butt = new wid_list_butt(this);
    list_butt->move(0,150);
    list_butt->set_pic(":/butt_choose_old.png");
    list_butt->set_size(3);
    list_butt->open();
    list_butt->start();
    list_butt->show();

    //插入到动画管理
    manage_move = new qt_manage(this);
    manage_move->set_wid_main(this);
    manage_move->set_pos_show(sys_info->pos());
    manage_move->set_pos_hide(QPoint(0,this->height()));
    manage_move->add_wid_vec(to_vec<QWidget*>
                             (sys_info,sys_wipe,sys_browser));
    manage_move->open(1);

    vlog("init finish");

    connect(list_butt,&wid_list_butt::fa_butt_index,this,[=](int index){
        manage_move->start_move(index);
//        out<<index;
    });

    connect(list_butt,&wid_list_butt::fa_finish,this,[=](direct dire,bool is_start){

//        out<<dire;
//        out<<is_start;
//        if(is_start) list_butt->close();
//        else list_butt->start();

    });
}
