#ifndef QT_RULES_H
#define QT_RULES_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QDir>
#include <QString>
#include <QFileInfo>
#include <QList>
#include <QRegExp>
#include <QDebug>

#include <stdlib.h>
#include <string>

using std::string;

class qt_rules : public QObject
{
    Q_OBJECT
public:
    explicit qt_rules(QObject *parent = nullptr);
    void set_path_conf(QString path);//配置文件路径

    //获取conf文件夹下的所有文件--非递归
    QStringList get_path_from_conf();

    //从单个文件中解析出匹配规则列表
    bool make_rules
        (QString path,QStringList &list_info,QStringList &list_path);

    //从单个规则中扫描出符合条件的路径到容器
    QStringList rules_to_files(QString str_rules);

    //发现是否存在"*"通配符，并返回路径"/"出现的次数
    int find_flg(QString str);

    //外部使用--解析出列表标题配置信息
    //参数为文件路径，分隔符
    static QStringList split_file(QString path,QString flg);

    //外部使用--从文件信息中切割出标记对列表标题对比
    //参数为列表标题，文件信息，返回结果的字符串，分割符
    //返回值是文件信息标记发现列表标题的位置
    static int split_pos(const QStringList &list,QString &str_find,
                         QString &str_content,QString flg = ":");

signals:

protected:
    QString v_path_conf;

    //获取文件全部信息
    static QFileInfoList get_files_info(QString path,bool is_into = true);
    static QStringList get_files_name(QString path,bool is_into = true);//获取文件名
    static QStringList get_path_dir(QString path,bool is_into = true);

    //获取可匹配路径--包括可变选项
    QStringList get_regex_dir(QString path_regex,bool is_variable);

//    //在路径列表中取文件路径与str_regex进行匹配
//    //匹配成功返回结果--包括可变选项，可选择是否递归
//    QStringList get_regex_files
//        (QStringList list_dir_regex,QString str_regex,bool is_into_dir);


//    //在路径列表中取文件路径与str_regex进行匹配
//    //匹配成功返回结果--包括可变选项，可选择是否递归
//    QStringList get_regex_dir
//        (QStringList list_dir_regex,QString str_regex,bool is_into_dir);


    //在路径列表中取文件路径与str_regex进行匹配
    //匹配成功返回结果--包括可变选项，可选择是否递归
    QStringList get_regex_func
        (QStringList (*)(QString path,bool is_into),
         QStringList list_dir_regex,QString str_regex,bool is_into_dir);
};

#endif // QT_RULES_H
