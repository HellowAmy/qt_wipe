#ifndef WID_TAB_LIST_H
#define WID_TAB_LIST_H

#include <QWidget>
#include <QSize>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QStringList>
#include <QPushButton>
#include <QVector>

//! 说明:
//! 该类是利用QTableWidget实现的显示列表
//! set_title函数指定标题，否则不美观
//! 可以通过open_choose函数开启全选和反选按钮
//! 必须通过set_size函数改变大小
//! 必须在最后调用open函数启动整个列表
//!
//! 调用顺序：
//! ...()
//! set_size()
//! open()
//!
class wid_tab_list : public QWidget
{
    Q_OBJECT
public:
    explicit wid_tab_list(QWidget *parent = nullptr);

    //设置标题
    void set_title(QString title,
                   QColor col = QColor(50,50,50,127));

    //添加内容
    void add_content(QStringList list,
                     QColor col = QColor(127,127,127,127));

    //打开全选按钮
    void open_choose(bool is_open = true,
                     QColor col = QColor(50,50,50,127));

    void set_size(int wide,int high,int space = 5);//设置大小窗口必须通过此函数
    QVector<int> get_check_status();//返回勾选状态
    void set_wide(int wide);
    void open();//启动列表

signals:
    emit void fa_press_choose();
    emit void fa_press_clear();

protected:
    QTableWidget *tab_list;//显示列表
    QTableWidget *tab_title;//标题
    QPushButton *butt_choose;//全选按钮
    QPushButton *butt_clear;//清空按钮

    QColor col_content;
    QSize size_wid;

    QStringList list_status;
    QVector<int> vec_status;

    int size_wide = 30;
    int v_space = 5;
};

#endif // WID_TAB_LIST_H
