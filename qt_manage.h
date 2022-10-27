#ifndef QT_MANAGE_H
#define QT_MANAGE_H

#include <QWidget>
#include <QObject>
#include <QVector>
#include <QTimer>

//=====全局模板，用于对QWidget*的转换=====
template<class TR>
QVector<TR> to_vec()
{
    QVector<TR> vec_wid;
    return vec_wid;
}

template<class TR,class T,class ...Tarr>
QVector<TR> to_vec(T arg,Tarr... arr)
{
    QVector<TR> vec_wid;
    vec_wid.push_back((TR)arg);

    QVector<TR> temp = to_vec<TR>(arr...);
    for(int i=0;i<temp.size();i++)
    {
        vec_wid.push_back(temp[i]);
    }

    return vec_wid;
}
//=====全局模板，用于对QWidget*的转换=====

enum enum_switch
{
    sw_first,
    sw_exit,
    sw_change_two,
};

//!
//! \brief The qt_manage class
//!
//!
//!
//!
class qt_manage : public QObject
{
    Q_OBJECT
public:
    explicit qt_manage(QObject *parent = nullptr);
    void set_wid_main(QWidget *wid);//设置主界面
    void set_pos_show(QPoint pos);//设置动画窗口原点位置
    void set_pos_hide(QPoint pos);//初始化窗口停靠位置
    void move_pos_wid(QPoint pos,int index_wid);//设置某个窗口的位置
    void move_pos_hide_all(QPoint pos);//所有窗口设置到隐藏点
    void hide_all();//隐藏所有窗口
    void add_wid_vec(QVector<QWidget*> vec);//添加到动画移动窗口

    bool exist_wid();
    int wid_index();

    bool open();//启动动画界面

    //播放动画，参数为界面索引和动画模式,双参数必须大于等于零
//    bool start_move(int index,int mode = 0);
    bool start_move(int index,int mode = 0,enum_switch status = sw_change_two);

    virtual void mode_show_abs();//留给子类继承的动画接口

signals:
    emit void fa_finish_index(int index);

protected:
    enum_switch sw_now;

    bool is_runing = false;//判断正在移动状态
    bool is_exist = false;//已经存在界面

    int v_speed = 5;//定时器速度
    int index_old = -1;//目前的窗口
    int index_new = -1;//操作最新窗口的索引
    int mode_show = 0;//设置动画模式

    QPoint pos_show;//界面进入窗口统一显示位置
    QPoint pos_hide;//界面进入窗口统一隐藏位置
    QWidget *wid_main;//主界面--所有的动画都相对于主界面进行操作
    QTimer *timer;

    QVector<QWidget*> vec_wid;//界面容器退出切换进入
    QVector<void (qt_manage::*)()> vec_wid_switch;//动画容器--切换
    QVector<void (qt_manage::*)()> vec_wid_first;//动画容器--进入
    QVector<void (qt_manage::*)()> vec_wid_exit;//动画容器--退出

    //自定义动画函数，需要手动结束定时器并返回完成信号
    void mode_switch_1();
    void mode_switch_2();
    void mode_switch_3();

    void mode_exit_1();
    void mode_exit_2();
    void mode_exit_3();

    void mode_first_1();
    void mode_first_2();
    void mode_first_3();


};

#endif // QT_MANAGE_H
