#ifndef QT_LIST_BUTT_H
#define QT_LIST_BUTT_H

#include <QWidget>
#include <QVector>
#include <QTimer>
#include <QPushButton>

enum enum_direct
{
    to_up,
    to_down,
    to_left,
    to_right
};

//! 说明:
//! 这个类将QPushButton指针放入容器中保持
//! 用定时器将按钮成列表展开
//! 支持四个方向，在direct中定义,支持默认按钮和自定按钮
//! 自定义按钮可以用add_butt_vec接口转为默认按钮既可完成展开
//! start_list和close_list函数分别控制列表的展开和收回
//! 在此之前需要调用open函数
//!
class qt_list_butt : public QWidget
{
    Q_OBJECT
public:
    explicit qt_list_butt(QWidget *parent = nullptr);
    ~qt_list_butt();

    QSize get_size_wid();//添加按钮后生成的界面大小
    int get_butt_count();//按钮数量

    void add_butt(int size);//添加默认按钮
    void add_butt_vec(QVector<QPushButton*> vec_butt);

    //按钮大小影响展开距离
    void set_butt_size(int wide,int high);
    void set_butt_size(QSize size);

    void open(enum_direct enum_direct = to_down);//启动定时器
    void start_list();
    void close_list();

    bool is_hide_wid(int index);//窗口是否隐藏
    bool status_start();//列表打开状态

signals:
    emit void fa_finish(enum_direct dire,bool status_start);
    emit void fa_move_list(bool status_start);
    emit void fa_butt_index(int index);

protected:
    enum_direct flg = to_down;//枚举四个不同方向的移动
    bool is_runing = false;
    bool is_add_out = false;//按钮来自外部
    bool is_start = false;//防止多次调用

    int v_space = 1;//按钮的间隔
    int v_speed = 10;//定时器速度
    int v_count_butt = 1;//按钮数量

    QSize size_butt;//按钮的大小，影响距离
    QSize size_wid;//整个窗口大小
    QVector<QPushButton*> vec_butt;//按钮容器

    QTimer *timer_move;

    void signal();
};

#endif // QT_LIST_BUTT_H
