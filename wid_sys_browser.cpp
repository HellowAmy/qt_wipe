#include "wid_sys_browser.h"

#include "qt_show.h"

wid_sys_browser::wid_sys_browser(QWidget *parent) : qt_frameless(parent)
{
    //清除按钮
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
    tab_list->set_title("文件名列表");
    tab_list->set_size(250,200);
    tab_list->open_choose();
    tab_list->open();
    tab_list->move(butt_clear->pos() +
                   QPoint(0,butt_clear->height() + space));

    //清除提示
    dialog_clear = new qt_dialog(this);
    dialog_clear->set_text("<<是否清空上网痕迹>>");

    //失败提示
    dialog_failed = new qt_dialog(this);
    dialog_failed->set_text("<<清空痕迹时遇到阻碍>>");

    //展开浏览器列表
    connect(this,&wid_sys_browser::fa_scan_browser,this,[=](){
        add_list_info();
    });

    //清除列表
    connect(tab_list,&wid_tab_list::fa_press_clear,this,[=](){
        list_conf.clear();
    });

    //清除
    connect(butt_clear,&QPushButton::clicked,this,[=](){
        dialog_clear->show();

    });

    //确认清除
    connect(dialog_clear,&qt_dialog::fa_press_ok,this,[=](){

        if(clear_browser() == false) dialog_failed->show();
        scan_browser();
    });

}

void wid_sys_browser::scan_browser()
{
    list_conf = files_info::get_files_path("../qt_wipe/conf");
    show_arr<QStringList>(list_conf);
    emit fa_scan_browser();
    vlog("扫描浏览器配置文件路径，并获取文件绝对路径");
}

bool wid_sys_browser::clear_browser()
{
    //获取打勾状态
    QVector<Qt::CheckState> vec = tab_list->get_status_vec();
    if(vec.size() != list_conf.size()) return false;

    //粉碎选中的浏览器文件
    QStringList list_leave;//排除粉碎文件--未打勾
    QStringList list_will_wipe;//即将粉碎的文件--打勾
    for(int i=0;i<vec.size();i++)
    {
        if(vec[i] == Qt::Checked) list_will_wipe<<list_conf[i];
        else list_leave<<list_conf[i];
    }

    //粉碎文件
    for(int i=0;i<list_will_wipe.size();i++)
    {
        //解析文件，拿到浏览器指定清除文件路径
        QVector<QString> vec = sys_section_file
                ::get_file_path(list_will_wipe[i]);

        //粉碎浏览器文件
        for(int i=0;i<vec.size();i++)
        {
            if(qt_wipe::wipe_path(vec[i]) == false)
                return false;
        }
    }

    return true;
}

void wid_sys_browser::add_list_info()
{
    //头部信息添加到列表
    QStringList list_head;
    for(int i=0;i<list_conf.size();i++)
    {
        QString temp = sys_section_file::get_file_head(list_conf[i]);
        if(temp.isEmpty() == false) list_head<<temp;
    }

    tab_list->set_content(list_head);
    show_arr<QStringList>(list_head,"添加到列表");
}
