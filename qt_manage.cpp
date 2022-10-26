#include "qt_manage.h"

#include "qt_show.h"

qt_manage::qt_manage(QObject *parent) : QObject(parent)
{
    vlog("init");

    timer = new QTimer(this);

    wid_main = nullptr;
    pos_show = QPoint(0,0);
    pos_hide = QPoint(0,0);

    //添加动画
    vec_mode_show.push_back(&qt_manage::mode_show_1);
    vec_mode_show.push_back(&qt_manage::mode_show_2);

    //定时器--动画信号
    connect(timer,&QTimer::timeout,this,[=](){
        mode_show_abs();
    });

    //动画结束信号
    connect(this,&qt_manage::fa_finish_mode,this,[=](){
        is_runing = false;
    });
}

void qt_manage::set_wid_main(QWidget *wid)
{
    wid_main = wid;
}

void qt_manage::add_wid_vec(QVector<QWidget *> vec)
{
    vec_wid = vec;
}

bool qt_manage::open(int index)
{
    bool is_ok = false;

    if(wid_main != nullptr && vec_wid.size() > 0
            && index < vec_wid.size())
    {
        move_pos_hide_all(pos_hide);//位置隐藏初始位置

        //显示默认窗口
        vec_wid[index]->move(pos_show);
        vec_wid[index]->show();
        index_old = index;
        is_ok = true;
    }

    vlog("开启动画，预设界面索引:%d,是否开启成功:%d",index,is_ok);

    return is_ok;
}

bool qt_manage::start_move(int index,int mode)
{
    if(is_runing == false && index != index_old)
    {
        if(index < vec_wid.size()
                && mode_show < vec_mode_show.size()
                && index >= 0 && mode >= 0)
        {
            vlog("列表移动,移动索引:%d",index);

            is_runing = true;
            index_new = index;//最新移动界面
            mode_show = mode;//启动动画模式类型
//            vec_wid[index]->move(pos_show);//初始化按钮位置
            timer->start(v_speed); 
        }
    }

    return is_runing;
}

//void qt_manage::close_move(int index)
//{
//    if(is_runing == false)
//    {
//        timer->start(10);
//    }
//}

void qt_manage::mode_show_abs()
{
    void (qt_manage::*ptr)() = vec_mode_show[mode_show];
    (this->*ptr)();
}

void qt_manage::mode_show_1()
{
    static int part = 1;//阶段标记
    static int count = 0;//计时器累计
    static int speed = 0;//移动速度
    static bool is_first = true;//首次进入
    static bool is_end = false;//结束标记

    if(is_first)
    {
        //新窗口位置
        vec_wid[index_new]->move(pos_show +
                 QPoint(0,-(pos_show.y() + vec_wid[index_new]->height())));

        vec_wid[index_new]->show();
        is_first = false;
    }

    count++;//定时器累加

    //第一阶段
    if(part == 1)
    {
        //间隔移动增加--实现阶段性加速
        static int space_add =
                (vec_wid[index_old]->width() * 2)
                / (vec_wid[index_old]->width() / 10);
        if((count % space_add) == 0) speed++;//加速

        //移动界面--旧窗口
        vec_wid[index_old]->move
                (vec_wid[index_old]->pos() + QPoint(speed,0));

        //停止条件
        if(vec_wid[index_old]->pos().x() > wid_main->width() * 2)
        {
            part = 2;//进入第二阶段

            //静态恢复初值
            count = 0;
            speed = 0;
        }
    }
    else if(part == 2)//第二阶段
    {
        //移动界面--新窗口
        vec_wid[index_new]->move
                (vec_wid[index_new]->pos() + QPoint(0,8));

        //停止条件
        if(vec_wid[index_new]->pos().y() > pos_show.y())
        {
            vec_wid[index_new]->move(pos_show);
            is_end = true;
        }
    }

    if(is_end)
    {
        timer->stop();//停止定时器

        //静态恢复初值
        part = 1;//阶段标记
        count = 0;//计时器累计
        speed = 0;//移动速度
        is_first = true;//首次进入
        is_end = false;//结束标记

        //迁移旧窗口
        vec_wid[index_old]->hide();
        vec_wid[index_old]->move(pos_hide);

        //刷新窗口标记，否则无法继续
        index_old = index_new;

        //必须发送结束信号，否则无法开启下一轮
        emit fa_finish_mode(mode_show);

        vlog("动画播放结束,现在的界面标记:%d",index_old);

    }
}

void qt_manage::mode_show_2()
{

}

void qt_manage::move_pos_hide_all(QPoint pos)
{
    vlog("初始化界面隐藏位置");
    for(int i=0;i<vec_wid.size();i++)
    {
        vec_wid[i]->move(pos);
        vec_wid[i]->hide();
    }
}

void qt_manage::set_pos_show(QPoint pos)
{
    pos_show = pos;
}

void qt_manage::set_pos_hide(QPoint pos)
{
    pos_hide = pos;

}

bool qt_manage::move_pos_wid(QPoint pos, int index_wid)
{
    bool is_ok = false;

    if(index_wid < vec_wid.size())
    {
        vec_wid[index_wid]->move(pos);
        is_ok = true;
    }

    return is_ok;
}
