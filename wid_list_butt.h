#ifndef WID_LIST_BUTT_H
#define WID_LIST_BUTT_H

#include <QWidget>

#include "qt_list_butt.h"
#include "qt_butt.h"

//! 说明:
//! 该类组合了qt_list_butt的展开列表
//! 应于嵌入到主界面中，并进行二次信号转发
//!
class wid_list_butt : public QWidget
{
    Q_OBJECT
public:
    explicit wid_list_butt(QWidget *parent = nullptr);
    void set_pic(QString pic);
    void set_size(int size);
    void open();
    void start();
    void close();

signals:
    emit void fa_finish(direct dire,bool is_start);
    emit void fa_butt_index(int index);

protected:
    int size_butt = 3;
    QString pic_butt;

    qt_list_butt *list_butt;

    void add_butt_list();

    void signal();

};

#endif // WID_LIST_BUTT_H
