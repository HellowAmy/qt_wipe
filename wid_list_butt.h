#ifndef WID_LIST_BUTT_H
#define WID_LIST_BUTT_H

#include <QWidget>

#include "qt_list_butt.h"
#include "qt_butt.h"

//! 说明:
//! 该类组合了qt_list_butt的展开列表
//! 应于嵌入到主界面中，并进行二次信号转发
//!
class wid_list_butt : public qt_list_butt
{
    Q_OBJECT
public:
    explicit wid_list_butt(QWidget *parent = nullptr);
    void add_butt(QString pic,int size);
    void set_butt_size_v();

signals:

protected:

};

#endif // WID_LIST_BUTT_H
