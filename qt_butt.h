#ifndef QT_BUTT_H
#define QT_BUTT_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QBitmap>

//! 说明:
//! 这个类用于改变QPushButton按钮的背景
//! 三个鼠标状态的贴图
//! open函数必须最后调用
//!
class qt_butt : public QPushButton
{
    Q_OBJECT
public:
    explicit qt_butt(QWidget *parent = nullptr);

    qt_butt(QString normal,QString enter,
            QString press,QWidget *parent = nullptr):
        QPushButton(parent),pic_normal(normal),
        pic_enter(press),pic_press(enter){}

    //开启按钮功能，必须在最后调用，否则不生效
    void open();

    //三种状态的图片
    void set_normal(QString pic);
    void set_enter(QString pic);
    void set_press(QString pic);

signals:

protected:
    bool is_open = false;

    QString pic_normal;
    QString pic_enter;
    QString pic_press;
    QString pic_change;

    QPixmap pix;

    void change_pic(QString pic);//切换图片
    void smooth_pic(QString pic);//图片平滑

    void paintEvent(QPaintEvent *e) override;
    void enterEvent(QEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void leaveEvent(QEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

};

#endif // QT_BUTT_H
