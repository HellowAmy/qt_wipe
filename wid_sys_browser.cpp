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
    QPalette palette_butt;
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



    //提示框
    lab_info = new QLabel(this);



    lab_info->setFont(QFont("微软雅黑",16));
    lab_info->setAlignment(Qt::AlignCenter);
    lab_info->setFrameShape(QFrame::Box);
    lab_info->setFrameShadow(QFrame::Sunken);
    lab_info->setLineWidth(3);
    lab_info->setMidLineWidth(3);
    lab_info->move(butt_clear->pos() +
                   QPoint(butt_clear->width() + space * space * 2 ,0));
    lab_info->resize(tab_list->width() / 4,tab_list->height() +
                     butt_clear->height() + space);

    lab_info->setText("点\n击\n清\n除\n痕\n迹");


//    //清除提示
//    dialog_clear = new qt_dialog(this);
//    dialog_clear->set_text("<<是否清空上网痕迹>>");

//    //失败提示
//    dialog_failed = new qt_dialog(this);
//    dialog_failed->set_text("<<清空痕迹时遇到阻碍>>");

    vlog("初始化浏览器清除窗口成功");

    //展开浏览器列表
    connect(this,&wid_sys_browser::fa_scan_browser,this,[=](){
        add_list_info();
    });

    //清除列表
    connect(tab_list,&wid_tab_list::fa_press_clear,this,[=](){
        list_conf.clear();
        lab_info->setText("");
        is_ready = false;
    });

    //清除
    connect(butt_clear,&QPushButton::clicked,this,[=](){

        if(list_conf.isEmpty())
        {
            scan_browser();
            lab_info->setText("点\n击\n清\n除\n痕\n迹");
            return;
        }
        else
        {
            if(is_ready == false)
            {
                is_ready = true;
                lab_info->setText("请\n谨\n慎\n选\n择");
            }
            else
            {
                is_ready = false;
                if(clear_browser()) lab_info->setText("完\n成\n清\n理");
                else lab_info->setText("清\n理\n遇\n到\n阻\n碍");
            }
        }
    });

//    //确认清除
//    connect(dialog_clear,&qt_dialog::fa_press_ok,this,[=](){

//        if(clear_browser() == false)
//        {
//            dialog_failed->show();
//            vlog("清除失败");
//        }
//        else vlog("清除成功");
//    });

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

        show_arr<QVector<QString>>(vec);
    }

    vlog("浏览器文件粉碎结束");

    list_conf = list_leave;//获取未粉碎信息

    //转为头信息
    QStringList list_temp;
    for(int i=0;i<list_conf.size();i++)
    {
        list_temp<<sys_section_file::get_file_head(list_conf[i]);
    }
    tab_list->set_content(list_temp);

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
