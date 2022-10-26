#include "wid_list_butt.h"

#include "qt_show.h"

wid_list_butt::wid_list_butt(QWidget *parent) : QWidget(parent)
{
    list_butt = new qt_list_butt(this);

    signal();
    vlog("init finish");
}

void wid_list_butt::set_pic(QString pic)
{
    pic_butt = pic;
}

void wid_list_butt::set_size(int size)
{
    size_butt = size;
}

void wid_list_butt::open()
{
    add_butt_list();
}

void wid_list_butt::start()
{
    list_butt->start_list();
}

void wid_list_butt::close()
{
    list_butt->close_list();
}

void wid_list_butt::add_butt_list()
{
    //==类型转换==
    QVector<qt_butt*> vec_butt_qt;
    for(int i=0;i<size_butt;i++)
    {
        qt_butt *temp = new qt_butt(this);
        temp->show();
        temp->set_normal(pic_butt);
        temp->move(0,0);
        temp->open();
        vec_butt_qt.push_back(temp);
    }

    QVector<QPushButton*> vec_butt_push;
    for(int i=0;i<vec_butt_qt.size();i++)
    {
        vec_butt_push.push_back((QPushButton*)vec_butt_qt[i]);
    }
    //==类型转换==

    list_butt->add_butt_vec(vec_butt_push);//添加按钮列表
    list_butt->open();//启动列表定时器
    vlog("类型转换完成,按钮数量:%d",list_butt->get_count_butt());

    this->resize(list_butt->get_size());
}

void wid_list_butt::signal()
{
    //信号转发——进行二次封装可以减少对基础类的污染
    connect(list_butt,&qt_list_butt::fa_finish,
            this,&wid_list_butt::fa_finish);

    connect(list_butt,&qt_list_butt::fa_butt_index,
            this,&wid_list_butt::fa_butt_index);

}
