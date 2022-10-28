#include "qt_manage.h"

#include "qt_show.h"

qt_manage::qt_manage(QObject *parent) : QObject(parent)
{
    vlog("init");

    timer = new QTimer(this);

    wid_main = nullptr;
    pos_show = QPoint(0,0);
    pos_hide = QPoint(0,0);

    //添加动画--切换
    vec_wid_switch.push_back(&qt_manage::mode_switch_1);
    vec_wid_switch.push_back(&qt_manage::mode_switch_2);
    vec_wid_switch.push_back(&qt_manage::mode_switch_3);

    //添加动画--进入
    vec_wid_first.push_back(&qt_manage::mode_first_1);
    vec_wid_first.push_back(&qt_manage::mode_first_2);
    vec_wid_first.push_back(&qt_manage::mode_first_3);

    //添加动画--退出
    vec_wid_exit.push_back(&qt_manage::mode_exit_1);
    vec_wid_exit.push_back(&qt_manage::mode_exit_2);
    vec_wid_exit.push_back(&qt_manage::mode_exit_3);


    //定时器--动画信号
    connect(timer,&QTimer::timeout,this,[=](){
        mode_show_abs();
    });

    //动画结束信号
    connect(this,&qt_manage::fa_finish_index,this,[=](){
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

bool qt_manage::exist_wid()
{
    return is_exist;
}

int qt_manage::wid_index()
{
    return index_old;
}

bool qt_manage::open()
{
    bool is_ok = false;

    if(wid_main != nullptr && vec_wid.size() > 0)
    {
        move_pos_hide_all(pos_hide);//位置隐藏初始位置
        is_ok = true;
    }

    vlog("开启动画,是否开启成功:%d",is_ok);

    return is_ok;
}

//bool qt_manage::start_move(int index,int mode)
//{
//    //窗口切换状态
//    if(is_runing == false && index != index_old)
//    {
//        if(index < vec_wid.size()
//                && mode_show < vec_wid_switch.size()
//                && index >= 0 && mode >= 0)
//        {
//            vlog("列表移动,移动索引:%d",index);

//            is_runing = true;
//            index_new = index;//最新移动界面
//            mode_show = mode;//启动动画模式类型
//            timer->start(v_speed);
//        }
//    }

//    //首次进入
//    else if(is_runing == false && index == index_old)
//    {
//        if(index < vec_wid.size()
//                && mode_show < vec_wid_switch.size()
//                && index >= 0 && mode >= 0)
//        {
//            vlog("同一个窗口:列表移动,移动索引:%d",index);

//            is_runing = true;
////            mode = 1;
////            index_new = index;//最新移动界面
//            mode_show = mode;//启动动画模式类型
//            timer->start(v_speed);
//        }
//    }

//    //窗口退出

//    return is_runing;
//}

bool qt_manage::start_move(int index, int mode, enum_switch status)
{
    //窗口切换状态
    if(is_runing == false && status == enum_switch::sw_change_two)
    {
        if(index < vec_wid.size()
                && mode_show < vec_wid_switch.size()
                && index >= 0 && mode >= 0)
        {
            index_new = index;//最新移动界面
            mode_show = mode;//启动动画模式类型

            //定时器启动条件
            if(index_new == -1 || index_old == -1)
            {
                vlog("定时器启动失败");
                return false;
            }

            is_runing = true;
            is_exist = true;
            sw_now = sw_change_two;

            timer->start(v_speed);
            vlog("启动定时器,移动索引:%d,动画类型%d,进入类型%d",index,mode_show,sw_now);
        }
        else vlog("参数输入无效,定时器启动失败");
    }

    //首次进入
    else if(is_runing == false && status == enum_switch::sw_first)
    {
        if(is_exist == false)
        {
            if(index < vec_wid.size()
                    && mode_show < vec_wid_first.size()
                    && index >= 0 && mode >= 0)
            {
                index_new = index;
                index_old = -1;

                //定时器启动条件
                if(index_new == -1 )
                {
                    vlog("定时器启动失败");
                    return false;
                }

                is_runing = true;
                is_exist = true;
                sw_now = sw_first;

                mode_show = mode;//启动动画模式类型
                timer->start(v_speed);

                vlog("启动定时器,移动索引:%d,动画类型%d,进入类型%d",index,mode_show,sw_now);
            }
        }
        else vlog("参数输入无效,定时器启动失败");
    }

    //窗口退出
    else if(is_runing == false && status == enum_switch::sw_exit)
    {

        if(index < vec_wid.size()
                && mode_show < vec_wid_exit.size()
                && index >= 0 && mode >= 0)
        {
            index_new = -1;
//            index_old = index;

            //定时器启动条件
            if(index_old == -1 )
            {
                vlog("定时器启动失败");
                return false;
            }

            is_runing = true;
            is_exist = false;
            sw_now = sw_exit;

            mode_show = mode;//启动动画模式类型
            timer->start(v_speed);

            vlog("启动定时器,移动索引:%d,动画类型%d,进入类型%d",index,mode_show,sw_now);
        }
        else vlog("参数输入无效,定时器启动失败");
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
    if(sw_now == sw_change_two)
    {
        void (qt_manage::*ptr)() = vec_wid_switch[mode_show];
        (this->*ptr)();
    }
    else if(sw_now == sw_first)
    {
        void (qt_manage::*ptr)() = vec_wid_first[mode_show];
        (this->*ptr)();
    }
    else if(sw_now == sw_exit)
    {
        void (qt_manage::*ptr)() = vec_wid_exit[mode_show];
        (this->*ptr)();
    }

}

void qt_manage::mode_switch_1()
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
        index_new = -1;

        //必须发送结束信号，否则无法开启下一轮
        emit fa_finish_index(index_old);

        vlog("动画播放结束");
    }
}

void qt_manage::mode_switch_2()
{

}

void qt_manage::mode_switch_3()
{

}

void qt_manage::mode_exit_1()
{

    static int count = 0;//计时器累计
//    static bool is_first = true;//首次进入
    static bool is_end = false;//结束标记

//    if(is_first)
//    {
//        //新窗口位置
//        vec_wid[index_old]->move(pos_show +
//                 QPoint(0,-(pos_show.y() + vec_wid[index_old]->height() * 3)));

//        vec_wid[index_old]->show();
//        is_first = false;
//    }

    count++;//定时器累加

    //移动界面
    vec_wid[index_old]->move
            (vec_wid[index_old]->pos() - QPoint(0,5));

    //停止条件
    if(vec_wid[index_old]->pos().y() < -wid_main->height() * 2)
    {
        vec_wid[index_old]->move(pos_hide);
        is_end = true;
    }

    if(is_end)
    {
        timer->stop();//停止定时器

        //静态恢复初值
        count = 0;//计时器累计
        is_end = false;//结束标记

        index_old = -1;
        index_new = -1;

        //必须发送结束信号，否则无法开启下一轮
        emit fa_finish_index(index_old);

        vlog("动画播放结束");
    }
}

void qt_manage::mode_exit_2()
{

}

void qt_manage::mode_exit_3()
{

}

void qt_manage::mode_first_1()
{
    static int count = 0;//计时器累计
    static bool is_first = true;//首次进入
    static bool is_end = false;//结束标记
    int index = index_new;

    if(is_first)
    {
        //新窗口位置
        vec_wid[index]->move(pos_show +
                 QPoint(0,-(pos_show.y() + vec_wid[index]->height() * 2)));

        vec_wid[index]->show();
        is_first = false;
    }

    count++;//定时器累加

    //移动界面
    vec_wid[index]->move
            (vec_wid[index]->pos() + QPoint(0,6));

    //停止条件
    if(vec_wid[index]->pos().y() > pos_show.y())
    {
        vec_wid[index]->move(pos_show);
        is_end = true;
    }

    if(is_end)
    {
        timer->stop();//停止定时器

        //静态恢复初值
        count = 0;//计时器累计
        is_first = true;//首次进入
        is_end = false;//结束标记

        //必须发送结束信号，否则无法开启下一轮
        index_old = index_new;//记录现存界面
        index_new = -1;
        emit fa_finish_index(index_old);

        vlog("动画播放结束");
    }










//    static int count = 0;//计时器累计
////    static bool is_first = true;//首次进入
//    static bool is_end = false;//结束标记

////    if(is_first)
////    {
////        //新窗口位置
////        vec_wid[index_old]->move(pos_show);
////        vec_wid[index_old]->show();
////        is_first = false;
////    }

//    count++;//定时器累加

//    //移动界面
//    vec_wid[index_old]->move
//            (vec_wid[index_old]->pos() + QPoint(0,-10));

//    //停止条件
//    if(vec_wid[index_old]->pos().y() > (wid_main->pos().y() + wid_main->height() * 2))
//    {
//        vec_wid[index_old]->hide();
//        is_end = true;
//    }

//    if(is_end)
//    {
//        timer->stop();//停止定时器

//        //静态恢复初值
//        count = 0;//计时器累计
////        is_first = true;//首次进入
//        is_end = false;//结束标记

//        //必须发送结束信号，否则无法开启下一轮
//        emit fa_finish_mode(mode_show);

//        vlog("动画播放结束,本次播放动画::mode_show_first");
//    }
}

void qt_manage::mode_first_2()
{

}

void qt_manage::mode_first_3()
{

}

void qt_manage::move_pos_hide_all(QPoint pos)
{
    vlog("显示窗口隐藏位置");
    for(int i=0;i<vec_wid.size();i++)
    {
        vec_wid[i]->move(pos);
        vec_wid[i]->hide();
    }
}

void qt_manage::hide_all()
{
    for(int i=0;i<vec_wid.size();i++)
    {
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

void qt_manage::move_pos_wid(QPoint pos, int index_wid)
{
    if(index_wid < vec_wid.size())
        vec_wid[index_wid]->move(pos);
}
