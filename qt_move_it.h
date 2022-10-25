#ifndef QT_MOVE_IT_H
#define QT_MOVE_IT_H

#include <QWidget>
#include <QVector>

class qt_move_it : public QWidget
{
    Q_OBJECT
public:
    explicit qt_move_it(QWidget *parent = nullptr);
    void set_pos(QPoint pos);
    void set_space(int space);
    void add_wid(QWidget *wid);//加入容器
    void set_hori();
    void set_vert();//垂直中心布局
    void set_vert(QPoint pos);//相对点垂直布局
    void set_hide();
    void set_show();
    int get_count_high();//获取控件累加高度

signals:

protected:
    QVector<QWidget*> vec;
    QWidget *v_parent;

    QPoint pos_origin;

    int v_space=0;

};

#endif // QT_MOVE_IT_H
