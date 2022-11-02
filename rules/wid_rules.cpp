#include "wid_rules.h"

#include "qt_show.h"

wid_rules::wid_rules(QWidget *parent) : QDialog(parent)
{
    this->resize(1200,400+30);
//    this->setWindowFlag(Qt::WindowStaysOnTopHint);//窗口置顶

    init();
    signal();

//    search_conf();
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

}

void wid_rules::signal()
{
    connect(butt_try,&QPushButton::clicked,this,[=](){
        tab_list->setRowCount(0);
        list_path_sum.clear();
        search_conf();
    });

    connect(butt_clear,&QPushButton::clicked,this,[=](){

        //粉碎文件
        QStringList list_less;
        for(const auto &a:list_path_sum)
        {
            if(qt_wipe::wipe_path(a) == false)
            {
                list_less<<a;
            }
        }

        //粉碎失败文件重新加入列表
        if(list_less.isEmpty() == false)
        {
            list_path_sum = list_less;
            tab_list->setRowCount(list_path_sum.size());

            //添加内容到列表
            for(int i=0;i<list_path_sum.size();i++)
            {
                //添加到列表--文件路径
                tab_list->setItem(i,0,new QTableWidgetItem(list_path_sum[i]));
                tab_list->setItem(i,1,new QTableWidgetItem("粉碎失败文件"));
            }
        }
        else
        {
            tab_list->setRowCount(0);
            list_path_sum.clear();
        }

    });
}
