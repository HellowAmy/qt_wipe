#include "widget.h"
#include "ui_widget.h"
#include "wid_main.h"

#include "qt_butt.h"
#include "qt_list_butt.h"

#include "qt_frameless.h"
#include "wid_sys_wipe.h"
#include "qt_manage.h"
#include "sys_info.h"
#include "qt_wipe.h"

#include "files_info.h"

#include "qt_dialog.h"

#include <QDebug>
#ifndef out
#define out qDebug()
#endif




Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

//    wid_sys_wipe *bu = new wid_sys_wipe(this);
//    bu->show();


    qt_dialog *hu = new qt_dialog(this);
    hu->show();


//    QFileInfoList list_info = files_info::get_files_info("/home/red/open/qt_hur");

//    QStringList list_name = files_info::get_files_name("/home/red/open/qt_hur");

//    for(int i=0;i<list_info.size();i++)
//    {
//        out<<list_info[i];
//    }

//    for(int i=0;i<list_name.size();i++)
//    {
//        out<<list_name[i];
//    }

//    for(auto a:list_info)
//    {

//    }



//    out<<qt_wipe::wipe_path("/home/red/1");
//    out<<qt_wipe::wipe_path("/home/red/01");
//    out<<qt_wipe::wipe_path("/home/red/01.txt");
//    out<<qt_wipe::wipe_path("/home/red/02.txt");
//    out<<qt_wipe::wipe_path("/home/red/11");


//    sys_info *hu = new sys_info_klin(this);
//    out<<"get_sys_version="<<hu->get_sys_version();
//    out<<"get_sys_cpu="<<hu->get_sys_cpu();
//    out<<"get_sys_mem="<<hu->get_sys_mem();
//    out<<"get_host="<<hu->get_host();
//    out<<"get_ip_net="<<hu->get_ip_net();


//    hu->

//    QWidget *h1 = new QWidget;
//    QWidget *h2 = new QWidget;
//    QWidget *h3 = new QWidget;
//    QWidget *h4 = new QWidget;

////    h3
//    QPushButton *hu = new QPushButton(h3);
//    hu->show();
//    hu->setText("11");

//    QVector<QWidget*> temp =  to_vec<QWidget*>(h1,h2,h3,h4);

//    out<<temp.size();

//    temp[2]->show();
//    temp[3]->show();



//    qt_frameless *u = new qt_frameless;
//    u->set_back(":/pic_title.png");
//    u->set_frameless(false);
//    u->show();



//    wid_main *hu = new wid_main;
//    hu->show();

//    qt_butt *w = new qt_butt(this);
//    w->set_normal(":/butt_choose_old.png");
//    w->open();

//    connect(w,&QPushButton::clicked,this,[=](){
//        out<<"was";
//    });




    //自定义按钮添加列表
//    QVector<qt_butt *> vec;
//    for(int i=0;i<3;i++)
//    {
//        qt_butt * te = new qt_butt(this);
//        te->set_normal(":/butt_choose_old.png");
//        te->open();
//        te->move(0,0);
//        vec.push_back(te);
//    }

//    QVector<QPushButton *> vec_org;
//    for(int i=0;i<vec.size();i++)
//    {
//        vec_org.push_back((QPushButton*)vec[i]);
//    }


//    qt_list_butt*f1 = new qt_list_butt(this);
////    f1->set_butt_size(vec[0]->size());
////    f1->add_butt(5);
//    f1->add_butt_vec(vec_org);

//    f1->open();
    //自定义按钮添加列表


}

Widget::~Widget()
{
    delete ui;
}

