#include "qt_dialog.h"

qt_dialog::qt_dialog(QWidget *parent) : QDialog(parent)
{
    butt_ok = new QPushButton(this);
    butt_no = new QPushButton(this);
    lab_info = new QLabel(this);

    size_screen = QSize(0,0);

    this->setWindowFlag(Qt::FramelessWindowHint);//无边框

    QList<QScreen *>  list = QGuiApplication::screens();
    if(list.size() > 0)
    {
        QScreen *screen = list[0];
        size_screen = screen->size();

        this->move(0,size_screen.height() / 2 - v_high / 2);
        this->resize(size_screen.width(),v_high);

        //设置输入框的背景透明（需要自定义添加背景）
//        QColor col(127,127,127,127);
//        QPalette palette;
//        palette.setColor(QPalette::Window,col);
//        this->setPalette(palette);
    }


//    butt_ok =
//    butt_no =
    int v_center_w = this->width() / 2;
    int v_center_h = this->height() / 2;
    int v_space = 5;
    lab_info->resize(500,50);
    lab_info->setFont(QFont("微软雅黑",16));
    lab_info->move(v_center_w - lab_info->width() / 2,
                   lab_info->height() / 10);
    lab_info->setText("=====================WW=========================================");
    lab_info->setFrameShape(QFrame::Box);
    lab_info->setFrameShadow(QFrame::Sunken);
    lab_info->setLineWidth(3);
    lab_info->setMidLineWidth(3);

    butt_ok->resize(100,30);
    butt_ok->move(v_center_w - (butt_ok->width()
                                + butt_ok->width() / 5 + v_space),
                  v_center_h / 2 + butt_ok->width() / 3);
    butt_ok->setText("ok");

    butt_no->resize(100,30);
    butt_no->move(v_center_w + (butt_ok->width() / 5 + v_space),
                  v_center_h / 2 + butt_ok->width() / 3);
    butt_no->setText("no");








}

void qt_dialog::set_text(QString txt)
{

}
