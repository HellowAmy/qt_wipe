#include "files_info.h"

files_info::files_info(QObject *parent) : QObject(parent)
{

}

QString files_info::get_host_path()
{
    QString str;
    str += QStandardPaths::writableLocation
            (QStandardPaths::HomeLocation);
    str += "/";
    return str;
}
