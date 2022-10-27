#include "wid_sys_info.h"

#include "qt_show.h"

wid_sys_info::wid_sys_info(QWidget *parent) : qt_frameless(parent)
{
    sys_info *info = new sys_info_klin(this);//虚函数
    set_info(info);
}

void wid_sys_info::set_info(sys_info *info)
{
    if(info != nullptr)
    {
        QLabel *lab_version = new QLabel(this);
        QLabel *lab_cpu = new QLabel(this);
        QLabel *lab_men = new QLabel(this);
        QLabel *lab_host = new QLabel(this);
        QLabel *lab_ip = new QLabel(this);

        QString str_version;
        QString str_cpu;
        QString str_men;
        QString str_host;
        QString str_ip;

        str_version = QString("系统信息：(内核：%1)(系统：%2)")
                .arg(info->get_sys_version().section(info->flg(),0,0))
                .arg(info->get_sys_version().section(info->flg(),1,1));

        str_cpu = QString("芯片信息：(型号：%1)(核心：%2)")
                .arg(info->get_sys_cpu().section(info->flg(),0,0))
                .arg(info->get_sys_cpu().section(info->flg(),1,1));

        str_men = QString("内存信息：(剩余：%1)(总量：%2)")
                .arg(info->get_sys_mem().section(info->flg(),0,0))
                .arg(info->get_sys_mem().section(info->flg(),1,1));

        str_host = QString("主机信息：(用户：%1)(主机：%2)")
                .arg(info->get_host().section(info->flg(),0,0))
                .arg(info->get_host().section(info->flg(),1,1));

        str_ip = QString("网络信息：(IP：%1)(掩码：%2)")
                .arg(info->get_ip_net().section(info->flg(),0,0))
                .arg(info->get_ip_net().section(info->flg(),1,1));

        lab_version->setText(str_version);
        lab_cpu->setText(str_cpu);
        lab_men->setText(str_men);
        lab_host->setText(str_host);
        lab_ip->setText(str_ip);

        QFont font("微软雅黑",13);
        lab_version->setFont(font);
        lab_cpu->setFont(font);
        lab_men->setFont(font);
        lab_host->setFont(font);
        lab_ip->setFont(font);

        int wide = 500;
        int high = 40;
        lab_version->resize(wide,high);
        lab_cpu->resize(wide,high);
        lab_men->resize(wide,high);
        lab_host->resize(wide,high);
        lab_ip->resize(wide,high);

        //添加到自动排版
        qt_move_it *move = new qt_move_it(this);
        move->add_wid(lab_version);
        move->add_wid(lab_cpu);
        move->add_wid(lab_men);
        move->add_wid(lab_host);
        move->add_wid(lab_ip);
        move->set_vert(QPoint(20,40));

        vlog("初始化信息窗口成功");


//        //===================================
//        QFont font("微软雅黑",13);
//        int wide = 500;
//        int high = 40;

//        QLabel *lab_version = new QLabel(this);
//        QString str_version;
//        str_version = QString("系统信息：(内核：%1)(系统：%2)")
//                .arg(info->get_sys_version().section(info->flg(),0,0))
//                .arg(info->get_sys_version().section(info->flg(),1,1));
//        lab_version->setText(str_version);
//        lab_version->setFont(font);
//        lab_version->resize(wide,high);

//        QLabel *lab_cpu = new QLabel(this);
//        QString str_cpu;
//        str_cpu = QString("芯片信息：(型号：%1)(核心：%2)")
//                .arg(info->get_sys_cpu().section(info->flg(),0,0))
//                .arg(info->get_sys_cpu().section(info->flg(),1,1));
//        lab_cpu->setText(str_cpu);
//        lab_cpu->setFont(font);
//        lab_cpu->resize(wide,high);

//        QLabel *lab_men = new QLabel(this);
//        QString str_men;
//        str_men = QString("内存信息：(剩余：%1)(总量：%2)")
//                .arg(info->get_sys_mem().section(info->flg(),0,0))
//                .arg(info->get_sys_mem().section(info->flg(),1,1));
//        lab_men->setText(str_men);
//        lab_men->setFont(font);
//        lab_men->resize(wide,high);

//        QLabel *lab_host = new QLabel(this);
//        QString str_host;
//        str_host = QString("主机信息：(用户：%1)(主机：%2)")
//                .arg(info->get_host().section(info->flg(),0,0))
//                .arg(info->get_host().section(info->flg(),1,1));
//        lab_host->setText(str_host);
//        lab_host->setFont(font);
//        lab_host->resize(wide,high);

//        QLabel *lab_ip = new QLabel(this);
//        QString str_ip;
//        str_ip = QString("网络信息：(IP：%1)(掩码：%2)")
//                .arg(info->get_ip_net().section(info->flg(),0,0))
//                .arg(info->get_ip_net().section(info->flg(),1,1));
//        lab_ip->setText(str_ip);
//        lab_ip->setFont(font);
//        lab_ip->resize(wide,high);

//        //添加到自动排版
//        qt_move_it *move = new qt_move_it(this);
//        move->add_wid(lab_version);
//        move->add_wid(lab_cpu);
//        move->add_wid(lab_men);
//        move->add_wid(lab_host);
//        move->add_wid(lab_ip);
//        move->set_vert(QPoint(20,40));
//        //===================================

    }
    else vlog("信息窗口指针为空");
}
