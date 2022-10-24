#include "qt_butt.h"

qt_butt::qt_butt(QWidget *parent) : QPushButton(parent)
{

}

void qt_butt::open()
{
    change_pic(pic_normal);
}

void qt_butt::set_normal(QString pic)
{
    pic_normal = pic;
}

void qt_butt::set_enter(QString pic)
{
    pic_enter = pic;
}

void qt_butt::set_press(QString pic)
{
    pic_press = pic;
}

void qt_butt::change_pic(QString pic)
{
    is_open = pix.load(pic);//首次进入
    if(is_open)
    {
        this->resize(pix.size());
        smooth_pic(pic);//平滑

        //设置png的按键透明映射（透明处不反应）
        this->setMask(pix.mask());
    }
    this->update();
}

void qt_butt::smooth_pic(QString pic)
{
    //拉伸
    if(pix.load(pic))
    {
        pix.scaled(pix.width(),pix.height(),
                   Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    }
}

void qt_butt::paintEvent(QPaintEvent *e)
{
    //打开成功
    if(is_open==true)
    {
        //画手
        QPainter *show = new QPainter(this);
        show->drawPixmap(pix.rect(),pix);
        show->end();
    }
    else QPushButton::paintEvent(e);//失败则使用父类
}

//鼠标进入
void qt_butt::enterEvent(QEvent *e)
{
    if(pic_enter!=NULL)
    {
        smooth_pic(pic_enter);
        this->update();
    }
    QPushButton::enterEvent(e);
}

//鼠标按下
void qt_butt::mousePressEvent(QMouseEvent *e)
{
    if(pic_press!=NULL)
    {
        smooth_pic(pic_press);
        this->update();
    }
    QPushButton::mousePressEvent(e);
}

//鼠标离开
void qt_butt::leaveEvent(QEvent *e)
{
    if(pic_normal!=NULL)
    {
        smooth_pic(pic_normal);
        this->update();
    }
    QPushButton::leaveEvent(e);
}

//鼠标释放
void qt_butt::mouseReleaseEvent(QMouseEvent *e)
{
    if(pic_enter!=NULL)
    {
        smooth_pic(pic_enter);
        this->update();
    }
    QPushButton::mouseReleaseEvent(e);
}
