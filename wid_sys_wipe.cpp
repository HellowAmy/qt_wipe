#include "wid_sys_wipe.h"

#include "qt_show.h"

wid_sys_wipe::wid_sys_wipe(QWidget *parent) : qt_frameless(parent)
{
    init();
    signal();
}

void wid_sys_wipe::clear_recover()
{
    QString path_files =
            files_info::get_host_path() + ".local/share/Trash/files";
    QString path_info =
            files_info::get_host_path() + ".local/share/Trash/info";

    int count_ok = 0;
    QDir dir;

    dir.setPath(path_files);
    if(dir.exists())
    {
        if(dir.removeRecursively()) count_ok++;
    }
    else count_ok++;

    dir.setPath(path_info);
    if(dir.exists())
    {
        if(dir.removeRecursively()) count_ok++;
    }
    else count_ok++;

    if(count_ok != 2) emit fa_failed_recover();
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

    dialog_wipe = new qt_dialog(this);
    dialog_wipe->set_text("<<粉碎文件将永远无法恢复>>");

    dialog_recover = new qt_dialog(this);
    dialog_recover->set_text("<<即将清空回收站>>");

    dialog_failed = new qt_dialog(this);

    vlog("初始化粉碎窗口成功");
}

void wid_sys_wipe::signal()
{
    //列表清空按钮
    connect(tab_list,&wid_tab_list::fa_press_clear,this,[=](){
        list_wipe.clear();
        vlog("粉碎文件列表清空");
    });

    //获取粉碎文件路径
    connect(edit_path,&QLineEdit::textEdited,this,[=](QString path){
        get_path_edit(path);
    });

    //清空失败--唤起弹窗
    connect(this,&wid_sys_wipe::fa_failed_recover,this,[=](){
        dialog_failed->set_text("清空回收站遇到阻止");
        dialog_failed->show();
        vlog("清空回收站遇到阻止");
    });

    //粉碎按钮--唤起弹窗
    connect(butt_wipe,&QPushButton::clicked,this,[=](){
        if(list_wipe.isEmpty() == false)
        {
            dialog_wipe->show();
            vlog("粉碎按钮--唤起弹窗");
        }
    });

    //粉碎--ok
    connect(dialog_wipe,&qt_dialog::fa_press_ok,this,[=](){
        wipe_list_file();
    });

    //回收按钮--唤起弹窗
    connect(butt_recover,&QPushButton::clicked,this,[=](){
        dialog_recover->show();
        vlog("回收按钮--唤起弹窗");
    });

    //回收--ok
    connect(dialog_recover,&qt_dialog::fa_press_ok,this,[=](){
        clear_recover();
    });

}

void wid_sys_wipe::get_path_edit(QString path)
{
    //重置显示
    edit_path->clear();
    edit_path->setText(str_edit_info);

    //处理文件路径字符串
    path = path.section("file://",1,1);//去头

    //去尾--兼容文件以/n结尾的Linux系统
    if(path.contains("\r\n")) path = path.section("\r\n",0,0);
    else path = path.section("\n",0,0);

    vlog("加到粉碎列表的路径:%s",path.toStdString().c_str());
    list_wipe<<path;//追加到现存列表
    tab_list->set_content(list_wipe);//放入列表
}

void wid_sys_wipe::wipe_list_file()
{
    if(list_wipe.isEmpty()) return;
    auto vec_status = tab_list->get_status_vec();//获取状态

    //分离打勾项
    QStringList list_leave;//排除粉碎文件--未打勾
    QStringList list_will_wipe;//即将粉碎的文件--打勾
    for(int i=0;i<list_wipe.size();i++)
    {
        if(i<vec_status.size()
                && vec_status[i] == Qt::Checked)
        {
            list_will_wipe<<list_wipe[i];
        }
        else list_leave<<list_wipe[i];
    }

    //粉碎打勾
    for(int i=0;i<list_will_wipe.size();i++)
    {
        //粉碎文件，粉碎失败加入列表
        bool is_ok = qt_wipe::wipe_path(list_will_wipe[i]);
        if(is_ok == false) list_leave<<list_will_wipe[i];
        vlog("粉碎成功：%d",is_ok);
    }

    //将保留项加入列表
    list_wipe = list_leave;
    tab_list->set_content(list_wipe);
}
