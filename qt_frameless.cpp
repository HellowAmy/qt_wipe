#include "qt_frameless.h"

qt_frameless::qt_frameless(QWidget *parent) : QWidget(parent)
{  

}

void qt_frameless::set_back(QString pic)
{
    pic_bake = pic;
    is_paint = true;
}

void qt_frameless::set_frameless(bool is_lucent)
{
    is_lessframe = true;
    this->setWindowFlag(Qt::FramelessWindowHint);//无边框
    if(is_lucent) this->setAttribute(Qt::WA_TranslucentBackground);//背景透明
}

void qt_frameless::paintEvent(QPaintEvent *e)
{
    //=====开启自绘背景=====
    if(is_paint)
    {
        QPainter *show=new QPainter(this);
        show->drawPixmap(0,0,QPixmap(pic_bake));
        show->end();
    }
    //=====开启自绘背景=====

    QWidget::paintEvent(e);

}

void qt_frameless::mouseMoveEvent(QMouseEvent *e)
{
    //=====开启无边框移动=====
    if(is_lessframe)
    {
        //判断防止抖动和LeftButton点击
        if(e->buttons() == Qt::LeftButton && is_press)
        {
            is_press=true;
            this->move(e->pos()-pos_global+this->pos());
        }
    }
    //=====开启无边框移动=====

    QWidget::mouseMoveEvent(e);
}

void qt_frameless::mousePressEvent(QMouseEvent *event)
{
    //=====开启无边框移动=====
    if(is_lessframe)
    {
        is_press = true;//允许移动——防止抖动
        pos_global = event->pos();//记录点击位置
    }
    //=====开启无边框移动=====

    QWidget::mousePressEvent(event);
}

void qt_frameless::mouseReleaseEvent(QMouseEvent *e)
{
    //=====开启无边框移动=====
    if(is_lessframe) is_press = false;//禁止移动——防止抖动
    //=====开启无边框移动=====

    QWidget::mouseReleaseEvent(e);
}
