#ifndef QT_DIALOG_H
#define QT_DIALOG_H

#include <QWidget>
#include <QDesktopWidget>
#include <QApplication>
#include <QScreen>
#include <QDialog>
#include <QLabel>
#include <QPushButton>

class qt_dialog : public QDialog
{
    Q_OBJECT
public:
    explicit qt_dialog(QWidget *parent = nullptr);

    void set_text(QString txt);

signals:
    emit void fa_press_ok();
    emit void fa_press_no();

protected:
    int v_high = 100;

    QSize size_screen;

    QPushButton *butt_ok;
    QPushButton *butt_no;
    QLabel *lab_info;



};

#endif // QT_DIALOG_H
