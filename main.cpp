#include "widget.h"
#include "wid_main.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

//    wid_main k;
//    k.show();

    return a.exec();
}
