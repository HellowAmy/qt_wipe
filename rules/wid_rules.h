#ifndef WID_RULES_H
#define WID_RULES_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QDialog>
#include <QPushButton>

#include "files_info.h"
#include "qt_rules.h"
#include "qt_wipe.h"

class wid_rules : public QDialog
{
    Q_OBJECT
public:
    explicit wid_rules(QWidget *parent = nullptr);

    void search_conf();
signals:

protected:
    qt_rules v_rules;
    QTableWidget *tab_list;

    QStringList list_path_sum;

    QPushButton *butt_clear;
    QPushButton *butt_try;

    void init();
    void signal();

};

#endif // WID_RULES_H
