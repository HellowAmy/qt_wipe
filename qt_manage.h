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

class qt_manage : public QObject
{
    Q_OBJECT
public:
    explicit qt_manage(QObject *parent = nullptr);
    void set_wid_main(QWidget *wid);//设置主界面
    void set_pos_show(QPoint pos);//设置动画窗口原点位置
    void set_pos_hide(QPoint pos);//初始化窗口停靠位置
    bool move_pos_wid(QPoint pos,int index_wid);//设置某个窗口的位置
    void move_pos_hide_all(QPoint pos);//所有窗口设置到隐藏点

    void add_wid_vec(QVector<QWidget*> vec);//添加到动画移动窗口

    bool open(int index = 0);//启动动画界面,显示默认窗口

    //播放动画，参数为界面索引和动画模式,双参数必须大于等于零
    bool start_move(int index,int mode = 0);

    virtual void mode_show_abs();//留给子类继承的动画接口

signals:
    emit void fa_finish_mode(int mode);

protected:
    bool is_runing = false;

    int v_speed = 5;
    int index_old = 0;
    int index_new = 0;//操作最新窗口的索引
    int mode_show = 0;//设置动画模式

    QPoint pos_show;//界面进入窗口统一显示位置
    QPoint pos_hide;//界面进入窗口统一隐藏位置
    QWidget *wid_main;//主界面--所有的动画都相对于主界面进行操作
    QTimer *timer;


    QVector<QWidget*> vec_wid;//界面容器
    QVector<void (qt_manage::*)()> vec_mode_show;//动画容器

    //自定义动画函数，需要手动结束定时器并返回完成信号
    void mode_show_1();
    void mode_show_2();


};

#endif // QT_MANAGE_H
