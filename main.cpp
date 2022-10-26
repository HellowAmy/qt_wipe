#include "widget.h"

#include "wid_main.h"
#include "qt_show.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

    vlog("ready in wid_main");

    wid_main k;
    k.show();

    return a.exec();
}
