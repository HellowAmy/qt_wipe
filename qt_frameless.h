#ifndef QT_FRAMELESS_H
#define QT_FRAMELESS_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

//! 说明:
//! 这个类是QWidget窗口的无边框版本
//! set_back函数通过图片自绘
//! set_frameless函数一旦调用就进入无边框移动模式
//! 参数true开启背景透明的效果
//!
class qt_frameless : public QWidget
{
    Q_OBJECT
public:
    explicit qt_frameless(QWidget *parent = nullptr);
    void set_back(QString pic);//设置背景图片
    void set_frameless(bool is_lucent = false);//启动无边框，默认不开启透明背景
    void set_range(QRect rect);

signals:

protected:
    //背景绘图
    bool is_paint = false;
    QString pic_bake;
    void paintEvent(QPaintEvent *e) override;

    //无边框移动
    bool is_lessframe = false;//开启标记——无边框移动
    bool is_press = false;//点击移动时防止抖动
    QPoint pos_global;//记录点击位置
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    //开启无边框范围点击
    bool is_range = false;
    QRect v_rect;

};

#endif // QT_FRAMELESS_H
