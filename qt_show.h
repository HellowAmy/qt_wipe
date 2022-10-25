#ifndef QT_SHOW_H
#define QT_SHOW_H


//#include "qt_show.h"

#include <QObject>
#include <QDebug>

#ifndef out
#define out qDebug()
#endif

template<class T>
void show(const T &buf)
{
    out<<buf;
}

template<class T>
void show_arr(const T vec,QString flg = "")
{
    if(flg != "")
    {
        out<<"=====";
        for(int i = 0;i<vec.size();i++)
        {
            out<<flg<<vec[i];
        }
        out<<"=====";
    }
    else
    {
        out<<"=====";
        for(int i = 0;i<vec.size();i++)
        {
            out<<vec[i];
        }
        out<<"=====";
    }

}

class qt_show : public QObject
{
    Q_OBJECT
public:
    explicit qt_show(QObject *parent = nullptr);

signals:

};

#endif // QT_SHOW_H
