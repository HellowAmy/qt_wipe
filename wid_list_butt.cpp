#include "wid_list_butt.h"

#include "qt_show.h"

wid_list_butt::wid_list_butt(QWidget *parent) : qt_list_butt(parent)
{
    this->hide();
}

void wid_list_butt::add_butt(QString pic, int size)
{
    //==类型转换==
    QVector<qt_butt*> vec_butt_qt;
    for(int i=0;i<size;i++)
    {
        qt_butt *temp = new qt_butt(this);
        temp->show();
        temp->set_normal(pic);
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

    this->add_butt_vec(vec_butt_push);//添加按钮列表
}


