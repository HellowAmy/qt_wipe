#include "qt_wipe.h"

qt_wipe::qt_wipe(QObject *parent) : QObject(parent)
{

}

bool qt_wipe::wipe_path(QString path)
{
    bool is_ok = false;

    if(path.isEmpty() == false)
    {
        QFileInfo info(path);
        if(info.exists())
        {
            char flg = 'f';
            std::string temp = path.toStdString();

            if(info.isDir()) flg = 'r';
            if(destroy_interface(temp.c_str(),flg) == 0) is_ok = true;
        }
        else is_ok = true;
    }

    return is_ok;
}
