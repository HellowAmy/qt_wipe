#include "qt_dialog.h"

qt_dialog::qt_dialog(QWidget *parent) : QDialog(parent)
{
    //必须单个使用，多个合并setWindowFlags函数会出现无效bug
    this->setWindowFlag(Qt::FramelessWindowHint);//无边框
    this->setWindowFlag(Qt::WindowStaysOnTopHint);//窗口置顶
    this->setWindowFlag(Qt::X11BypassWindowManagerHint);//隐藏弹出窗口

    this->setWindowModality(Qt::WindowModal);//模态
    this->hide();

    size_screen = QSize(0,0);

    //获取屏幕大小
    QList<QScreen *>  list = QGuiApplication::screens();
    if(list.size() > 0)
    {
        QScreen *screen = list[0];
        size_screen = screen->size();

        this->move(0,size_screen.height() / 2 - v_high / 2);
        this->resize(size_screen.width(),v_high);
    }

    int v_center_w = this->width() / 2;
    int v_center_h = this->height() / 2;
    int v_space = 5;

    //提示框
    lab_info = new QLabel(this);
    lab_info->resize(500,50);
    lab_info->setFont(QFont("微软雅黑",16));
    lab_info->setText("提示内容");
    lab_info->setAlignment(Qt::AlignCenter);
    lab_info->setFrameShape(QFrame::Box);
    lab_info->setFrameShadow(QFrame::Sunken);
    lab_info->setLineWidth(3);
    lab_info->setMidLineWidth(3);
    lab_info->move(v_center_w - lab_info->width() / 2,
                   lab_info->height() / 10);

    //按钮--ok
    butt_ok = new QPushButton(this);
    butt_ok->show();
    butt_ok->resize(100,30);
    butt_ok->setText("ok");
    butt_ok->move(v_center_w - (butt_ok->width()
                                + butt_ok->width() / 5 + v_space),
                  v_center_h / 2 + butt_ok->width() / 3);

    //按钮--no
    butt_no = new QPushButton(this);
    butt_no->show();
    butt_no->resize(100,30);
    butt_no->setText("no");
    butt_no->move(v_center_w + (butt_ok->width() / 5 + v_space),
                  v_center_h / 2 + butt_ok->width() / 3);

    //信号转发
    connect(butt_ok,&QPushButton::clicked,this,&qt_dialog::fa_press_ok);
    connect(butt_no,&QPushButton::clicked,this,&qt_dialog::fa_press_no);
    connect(butt_ok,&QPushButton::clicked,this,&qt_dialog::hide);
    connect(butt_no,&QPushButton::clicked,this,&qt_dialog::hide);

//    connect(this,&qt_dialog::fa_press_ok,this,[=](){
//        this->hide();
//    });
//    connect(this,&qt_dialog::fa_press_no,this,[=](){
//        this->hide();
//    });
}

void qt_dialog::set_text(QString txt)
{
    lab_info->setText(txt);
}
