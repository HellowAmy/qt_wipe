#include "wid_main.h"

#include "qt_show.h"

wid_main::wid_main(QWidget *parent) : qt_frameless(parent)
{
    QRect v_rect = QRect (0,0,150,150);//范围移动点击

    //主窗口的设置
    this->set_back(":/pic_title.png");
    this->set_frameless(true);
//    this->set_frameless(false);
    this->set_range(v_rect);
    this->resize(670,280+(150/2));

    //系统信息
    sys_info = new wid_sys_info(this);
    sys_info->set_back(":/pic_info.png");
    sys_info->resize(520,280);
    sys_info->move(150,150 / 2);

    //文件粉碎
    sys_wipe = new wid_sys_wipe(this);
    sys_wipe->set_back(":/pic_info.png");
    sys_wipe->resize(520,280);
    sys_wipe->hide();

    //浏览器清除
    sys_browser = new wid_sys_browser(this);
    sys_browser->set_back(":/pic_info.png");
    sys_browser->resize(520,280);
    sys_browser->hide();

    //按键容器列表
    list_butt = new wid_list_butt(this);
    list_butt->resize(list_butt->get_size_wid());
    list_butt->move(0,150);
    list_butt->add_butt(":/butt_choose_old.png",3);
    list_butt->open();

    //插入到动画管理
    manage_move = new qt_manage(this);
    manage_move->set_wid_main(this);
    manage_move->set_pos_show(sys_info->pos());
    manage_move->set_pos_hide(QPoint(0,this->height()));
    manage_move->add_wid_vec
            (to_vec<QWidget*>(sys_info,sys_wipe,sys_browser));
    manage_move->open();



    //===== 关闭程序 =====
    //关闭程序按钮
    qt_butt *butt_close = new qt_butt(this);
    butt_close->move(0,0);
    butt_close->set_normal(":/pic_close.png");
    butt_close->open();

    //关闭程序信号
    connect(butt_close,&qt_butt::clicked,this,&wid_main::close);
    //===== 关闭程序 =====



    //点击按钮列表
    connect(list_butt,&wid_list_butt::fa_butt_index,this,[=](int index){

        if(manage_move->exist_wid() == false)//界面首次进入
        {
            manage_move->start_move(index,0,sw_first);
        }
        else if(manage_move->wid_index() != index)//界面切换
        {
            manage_move->start_move(index,0,sw_change_two);
        }
    });

    //结束时发送窗口号
    connect(manage_move,&qt_manage::fa_finish_index,[=](int index){

        if(index == 2) sys_browser->scan_browser();
    });

    //右键展开按钮列表
    connect(this,&wid_main::fa_press_right,this,[=](){

        //按钮列表--展开
        if(list_butt->status_start() == false)
        {
            list_butt->start_list();
        }

        //按钮列表--关闭
        else if(list_butt->status_start())
        {
            list_butt->close_list();
            manage_move->start_move(0,0,sw_exit);//退出,第一个参数无效
        }
    });
}

void wid_main::mousePressEvent(QMouseEvent *event)
{
    qt_frameless::mousePressEvent(event);

    if(event->button() == Qt::RightButton)
    {
        if(v_rect.contains(event->pos())) emit fa_press_right();
    }

}
