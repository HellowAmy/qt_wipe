#include "wid_rules.h"

#include "qt_show.h"

wid_rules::wid_rules(QWidget *parent) : QDialog(parent)
{
    this->resize(600,400+30);

    pp_list_all = nullptr;

//    this->setWindowFlag(Qt::WindowStaysOnTopHint);//窗口置顶

    init();
    signal();
//    search_conf();

//    search_files();
//    search_files();
//    search_files();

}

wid_rules::~wid_rules()
{
    //多级指针释放内存
    if(pp_size > 0)
    {
        for(int i=0;i<pp_size;i++)
        {
            delete pp_list_all[i];
            pp_list_all[i] = nullptr;
        }

        delete[] pp_list_all;
        pp_list_all = nullptr;
        pp_size = 0;
    }
}

void wid_rules::search_conf()
{
    QString temp_path = "../qt_wipe/rules/tab_label.conf";
    QStringList list_title = qt_rules::split_file(temp_path,"##");

    tab_list->setColumnCount(list_title.size());
    tab_list->setHorizontalHeaderLabels(list_title);

    tab_list->horizontalHeader()->setStretchLastSection(true);
    tab_list->horizontalHeader()->setSectionResizeMode
            (QHeaderView::ResizeToContents);

    QString path_conf = "../qt_wipe/rules/conf";
    v_rules.set_path_conf(path_conf);

    //获取conf文件夹下的所有文件--非递归
    QStringList list = v_rules.get_path_from_conf();

    int index_end = 0;//计算累积量，标记现存列表结尾
    for(int i=0;i<list.size();i++)
    {
        vlog("扫描文件名: %s",list[i].toStdString().c_str());

        QStringList list_info;
        QStringList list_path;

        //从单个文件中解析出匹配规则列表
        v_rules.make_rules(list[i],list_info,list_path);

        //获取文件内所有规则匹配出的文件路径
        QStringList list_all;
        for(int i=0;i<list_path.size();i++)
        {
            vlog("规则: %s",list_path[i].toStdString().c_str());

            //从单个规则中扫描出符合条件的路径
            list_all += v_rules.rules_to_files(list_path[i]);
        }

        //新内容增加到列表,提前设置大小
        tab_list->setRowCount(tab_list->rowCount() + list_all.size());

        //添加内容到列表
        for(int i=0;i<list_all.size();i++)
        {
            //添加到列表--文件路径
            tab_list->setItem(index_end + i,0,new QTableWidgetItem(list_all[i]));

            //添加到列表--文件信息
            for(int t=0;t<list_info.size();t++)
            {
                //解析出文件信息对应的标题位置
                QString content;
                int index = qt_rules::split_pos
                        (list_title,list_info[t],content);

                //不为空添加内容--不判断插入位置为-1会出错
                if(index != -1)
                {
                    tab_list->setItem(index_end + i,index,
                                      new QTableWidgetItem(content));
                }
            }
        }

        index_end += list_all.size();
        list_path_sum += list_all;

        vlog("单文件扫描获取结果总数: %d",list_all.size());
    }

    vlog("表格底线位置: %d",list_path_sum.size());
}

void wid_rules::search_files()
{
    //读取列表信息
    QString temp_path = "../qt_wipe/rules/tab_label.conf";
    QStringList list_title = qt_rules::split_file(temp_path,"##");

    //设置配置文件路径
    QString path_conf = "../qt_wipe/rules/conf";
    v_rules.set_path_conf(path_conf);

    //获取conf文件夹下的所有文件--非递归
    QStringList list = v_rules.get_path_from_conf();

    //设置表格
    tab_list->setRowCount(list.size());
    tab_list->setColumnCount(list_title.size());
    tab_list->setHorizontalHeaderLabels(list_title);
    tab_list->horizontalHeader()->setStretchLastSection(true);

    show_arr<QStringList>(list_title,"列表标题");


    //===== 多级指针内存分配和释放 =====
    //如果已经存在内存--多级指针释放内存
    if(pp_size > 0)
    {
        for(int i=0;i<pp_size;i++)
        {
            delete pp_list_all[i];
            pp_list_all[i] = nullptr;
        }
        delete[] pp_list_all;
        pp_list_all = nullptr;
        pp_size = 0;
    }

    //多级指针分配空间
    pp_size = list.size();
    pp_list_all = new QStringList*[pp_size];
    for(int i=0;i<pp_size;i++)
    {
        pp_list_all[i] = new QStringList;
    }
    //===== 多级指针内存分配和释放 =====


    //扫描配置文件
    for(int i=0;i<list.size();i++)
    {
        QStringList list_info;
        QStringList list_path;

        //从单个文件中解析出匹配规则列表
        v_rules.make_rules(list[i],list_info,list_path);

        //获取文件内所有规则匹配出的文件路径
        QStringList list_all;
        for(int i=0;i<list_path.size();i++)
        {
            vlog("规则: %s",list_path[i].toStdString().c_str());

            //从单个规则中扫描出符合条件的路径
            list_all += v_rules.rules_to_files(list_path[i]);
        }

        *pp_list_all[i] = list_all;

        //获取配置文件下所有文件大小
        int size_sum = 0;
        for(int i=0;i<list_all.size();i++)
        {
            QFileInfo info(list_all[i]);
            size_sum += info.size();

        }

        //添加到列表--文件信息
        for(int t=0;t<list_info.size();t++)
        {
            //解析出文件信息对应的标题位置
            QString content;
            int index = qt_rules::split_pos
                    (list_title,list_info[t],content);

            if(index != -1)
            {
                //显示表格标题，判断变量参数
                if(content == "%SIZE%")
                {
                    out<<index<<"|"<<content<<"|"<<"SIZE";
                    content = QString::number(size_sum / 1024) + " K";
                    tab_list->setItem(i,index,
                                      new QTableWidgetItem(content));
                }
                else if(content == "%COUNT%")
                {
                    out<<index<<"|"<<content<<"|"<<"COUNT";
                    content = QString::number(list_all.size());
                    tab_list->setItem(i,index,
                                      new QTableWidgetItem(content));
                }
                else if(content == "%CONF%")
                {
                    out<<index<<"|"<<content<<"|"<<"COUNT";
                    content = list[i].section("/",-1,-1);
                    tab_list->setItem(i,index,
                                      new QTableWidgetItem(content));
                }
                else//固定内容显示
                {
                    out<<index<<"|"<<content;
                    tab_list->setItem(i,index,
                                      new QTableWidgetItem(content));
                }
            }
        }

        tab_list->item(i,0)->setCheckState(Qt::Checked);//添加复选框
    }
}

void wid_rules::init()
{
    tab_list = new QTableWidget(this);
    tab_list->resize(this->size() - QSize(0,30));
    tab_list->show();

    butt_try = new QPushButton(this);
    butt_try->setText("重新扫描");
    butt_try->resize(this->width() / 2,30);
    butt_try->move(QPoint(0,tab_list->height()));
    butt_try->show();

    butt_clear = new QPushButton(this);
    butt_clear->setText("清除文件");
    butt_clear->resize(this->width() / 2,30);
    butt_clear->move(QPoint(this->width() / 2,tab_list->height()));
    butt_clear->show();


    QHBoxLayout *box = new QHBoxLayout(this);
    box->addWidget(tab_list);
    this->setLayout(box);
}

void wid_rules::signal()
{
    connect(butt_try,&QPushButton::clicked,this,[=](){
        tab_list->setRowCount(0);
        search_files();
    });

    connect(butt_clear,&QPushButton::clicked,this,[=](){

        //加入粉碎清单
        QStringList list_clear;
        for(int i=0;i<tab_list->rowCount();i++)
        {
            if(tab_list->item(i,0)->checkState() == Qt::Checked)
            {
                list_clear += *pp_list_all[i];
            }
        }

        show_arr<QStringList>(list_clear,"粉碎文件清单");

        //粉碎文件
        QStringList list_less;
        for(const auto &a:list_clear)
        {
            if(qt_wipe::wipe_path(a) == false)
            {
                list_less<<a;
            }
        }

        tab_list->setRowCount(0);
        vlog("粉碎完成");
//        tab_list->setRowCount(list_less.size());//粉碎失败的文件

    });
}
