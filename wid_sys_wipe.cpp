#include "wid_sys_wipe.h"

#include <QDebug>
#ifndef out
#define out qDebug()
#endif

wid_sys_wipe::wid_sys_wipe(QWidget *parent) : qt_frameless(parent)
{
    init();
    signal();
}

void wid_sys_wipe::init()
{
    //全部布局以输入框为基准点
    str_edit_info = "<<将粉碎文件拖入此处>>";
    int space = 5;//控件的间隔
    edit_path = new QLineEdit(this);
    edit_path->resize(340,30);
    edit_path->move(40,20);
    edit_path->setAlignment(Qt::AlignCenter);
    edit_path->setText(str_edit_info);
    edit_path->show();

    //粉碎按钮
    butt_wipe = new QPushButton(this);
    butt_wipe->resize(100,30);
    butt_wipe->move(edit_path->pos() +
                    QPoint(edit_path->width() + space,0));
    butt_wipe->setText("文件粉碎");
    butt_wipe->show();

    //清空回收站 (位置在粉碎按钮下方)
    butt_recover = new QPushButton(this);
    butt_recover->resize(100,200);
    butt_recover->move(butt_wipe->pos() +
                       QPoint(0, butt_wipe->height() + space));
    butt_recover->setText("清\n空\n回\n收\n站");
    butt_recover->show();

    //==半透明==
    //设置输入框的背景透明（需要自定义添加背景）
    QColor col(50,50,50,127);
    QPalette palette;

    palette.setColor(QPalette::Base,col);
    edit_path->setPalette(palette);

    //设置按钮透明背景（需要自定义添加背景）
    QPalette palette_butt;//QPalette::Base
    palette_butt.setColor(QPalette::Button,col);

    butt_wipe->setFlat(true);
    butt_wipe->setAutoFillBackground(true);
    butt_wipe->setPalette(palette_butt);

    butt_recover->setFlat(true);
    butt_recover->setAutoFillBackground(true);
    butt_recover->setPalette(palette_butt);
    //==半透明==

    //显示粉碎路径文件名列表
    tab_list = new wid_tab_list(this);
    tab_list->show();
    tab_list->move(edit_path->pos() +
                   QPoint(0,edit_path->height() + space));
    tab_list->open_choose();
    tab_list->set_title("文件名列表");
    tab_list->set_size(340,200);
    tab_list->open();
}

void wid_sys_wipe::signal()
{
    //列表清空按钮
    connect(tab_list,&wid_tab_list::fa_press_clear,this,[=](){
        list_wipe.clear();
    });



    //粉碎按钮
    connect(butt_wipe,&QPushButton::clicked,this,[=](){
        wipe_list_file();
    });



    //获取粉碎文件路径
    connect(edit_path,&QLineEdit::textEdited,this,[=](QString path){
        get_path_edit(path);
    });
}
#include "qt_show.h"

void wid_sys_wipe::get_path_edit(QString path)
{

//    list_wipe<<path;

    //重置显示
    edit_path->clear();
    edit_path->setText(str_edit_info);

    //处理文件路径字符串
    path = path.section("file://",1,1);//去头

    //去尾--兼容文件以/n结尾的Linux系统
    if(path.contains("\r\n")) path = path.section("\r\n",0,0);
    else path = path.section("\n",0,0);

//    tab_list->clear_list();//清空列表
//    list_wipe = files_info::get_files_name(path);//添加到列表

//    //去除路径
//    QStringList list_less_dir;
//    for(int i=0;i<list_wipe.size();i++)
//    {
//        list_less_dir<<list_wipe[i].section("/",-1,-1);
//    }




//    out<<path;
//    tab_list->add_content(QStringList(path));
    list_wipe<<path;

    show_arr<QStringList>(list_wipe,"123");
//    for(int i=0;i<list_wipe.size();i++)
//    {
//        out<<list_wipe;
//    }
    tab_list->set_content(list_wipe);//放入列表
}

void wid_sys_wipe::wipe_list_file()
{
    if(list_wipe.isEmpty()) return;

    //获取状态
    QVector<Qt::CheckState> vec_status = tab_list->get_status_vec();



    QStringList list_leave;//排除粉碎文件
    QStringList list_will_wipe;//即将粉碎的文件
    for(int i=0;i<list_wipe.size();i++)
    {
        if(i<vec_status.size()
                && vec_status[i] == Qt::Checked)
        {
            list_will_wipe<<list_wipe[i];
        }
        else list_leave<<list_wipe[i];
    }

    for(int i=0;i<list_will_wipe.size();i++)
    {
        //粉碎文件，粉碎失败加入列表
        bool is_ok = qt_wipe::wipe_path(list_will_wipe[i]);
        if(is_ok == false) list_leave<<list_will_wipe[i];
    }


    out<<"11asd=========";
    show_arr<QStringList>(list_leave);
    out<<"asd=========";
    show_arr<QStringList>(list_will_wipe);

    //==
    show_arr<QStringList>(list_wipe,"==");


    //将保留项加入列表
    list_wipe = list_leave;
    tab_list->set_content(list_wipe);
    tab_list->update();


}
