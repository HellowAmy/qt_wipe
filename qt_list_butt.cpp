#include "qt_list_butt.h"

#include "qt_show.h"

qt_list_butt::qt_list_butt(QWidget *parent) : QWidget(parent)
{
    timer_move = new QTimer(this);

    size_butt = QSize(100,30);
    signal();

    this->hide();
}

qt_list_butt::~qt_list_butt()
{
    for(int i=0;i<vec_butt.size();i++)
    {
        delete vec_butt[i];
    }
}

void qt_list_butt::add_butt(int size)
{
    v_count_butt = size;
}

void qt_list_butt::add_butt_vec(QVector<QPushButton *> vec)
{
    //从容器中添加列表，主要用于支持子类的转换
    for(int i=0;i<vec.size();i++)
    {
        vec_butt.push_back(vec[i]);
        vec_butt[i]->move(0,0);
    }
    v_count_butt = vec_butt.size();

    if(vec_butt.size() > 0) size_butt = vec_butt[0]->size();
    is_add_out = true;

    vlog("添加到按钮容器,按钮数量:%d",vec_butt.size());
}

void qt_list_butt::set_butt_size(int wide, int high)
{
    size_butt = QSize(wide,high);
}

void qt_list_butt::set_butt_size(QSize size)
{
    size_butt = size;
}

QSize qt_list_butt::get_size_wid()
{
    return size_wid;
}

int qt_list_butt::get_butt_count()
{
    return vec_butt.size();
}

void qt_list_butt::open(enum_direct direct)
{
    vlog("默认隐藏,初始化列表设置,展开方向:%d",direct);

    //默认添加的按钮
    if(is_add_out == false)
    {
        for(int i=0;i<v_count_butt;i++)
        {
            QPushButton *temp = new QPushButton(this);
            temp->resize(size_butt);
            temp->move(0,0);
            temp->show();
            vec_butt.push_back(temp);
        }
    }

    //四个方向的界面大小预留位置
    if(direct == to_down)
    {
        this->resize(size_butt + QSize
                (0,size_butt.height() * v_count_butt));
        size_wid = this->size();
    }
    else if(direct == to_up)
    {

    }
    else if(direct == to_left)
    {

    }
    else if(direct == to_right)
    {

    }

    flg = direct;//记录展开位置

    //加入按钮的点击信号
    for(int i=0;i<vec_butt.size();i++)
    {
        connect(vec_butt[i],&QPushButton::clicked,this,[=](){
            emit fa_butt_index(i);
        });
    }
}

void qt_list_butt::start_list()
{
    if(is_runing == false)
    {
        vlog("列表状态--展开");
        emit fa_move_list(true);
    }
}

void qt_list_butt::close_list()
{
    if(is_runing == false)
    {
        vlog("列表状态--关闭");
        emit fa_move_list(false);
    }
}

bool qt_list_butt::is_hide_wid(int index)
{
    return vec_butt[index]->isHidden();
}

bool qt_list_butt::status_start()
{
    return is_start;
}

void qt_list_butt::signal()
{
    //定时器--移动按钮信号槽
    connect(timer_move,&QTimer::timeout,this,[=](){
        static int count_in = 0;//移动距离
        static int count_move = 0;//移动停止标记

        count_in++;

        //四个方向对应移动操作
        if(flg == to_down)
        {
            count_move = size_butt.height() + v_space;
            for(int i=0;i<vec_butt.size();i++)
            {
                //判断展开或关闭
                int temp = i;
                if(is_start == false) temp = -temp;

                vec_butt[i]->move(vec_butt[i]->pos() + QPoint(0,temp));
            }
        }
        else if(flg == to_up)
        {

        }
        else if(flg == to_left)
        {

        }
        else if(flg == to_right)
        {

        }

        //定时器结束
        if(count_in == count_move)
        {
            timer_move->stop();
            count_move = 0;
            count_in = 0;
            emit fa_finish(flg,is_start);

            vlog("列表展开结束");
        }
    });

    //关闭列表后隐藏
    connect(this,&qt_list_butt::fa_finish,this,[=](enum_direct,bool is_start){
        if(is_start == false) this->hide();
        is_runing = false;
    });

    //列表移动--展开或关闭
    connect(this,&qt_list_butt::fa_move_list,this,[=](bool start){
        this->show();
        is_runing = true;
        is_start = start;//展开或者关闭标记
        timer_move->start(v_speed);//开启定时器
    });
}
