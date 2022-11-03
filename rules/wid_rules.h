#ifndef WID_RULES_H
#define WID_RULES_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QDialog>
#include <QPushButton>
#include <QFileInfo>
#include <QHBoxLayout>

#include "files_info.h"
#include "qt_rules.h"
#include "qt_wipe.h"

class wid_rules : public QDialog
{
    Q_OBJECT
public:
    explicit wid_rules(QWidget *parent = nullptr);
    ~wid_rules();

    void search_conf();
    void search_files();
signals:

protected:
    int pp_size = 0;
    qt_rules v_rules;//扫描规则
    QTableWidget *tab_list;

    //多级指针，用于操作扫描到的文件，进行单独管理
    QStringList **pp_list_all;

    //search_conf函数使用--废弃
    QStringList list_path_sum;

    QPushButton *butt_clear;
    QPushButton *butt_try;

    void init();
    void signal();

};

#endif // WID_RULES_H
