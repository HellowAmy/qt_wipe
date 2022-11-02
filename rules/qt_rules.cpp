#include "qt_rules.h"

#include "qt_show.h"

qt_rules::qt_rules(QObject *parent) : QObject(parent)
{

//    set_path_conf("/home/red/open/work/test_qt/conf");


//    //获取conf文件夹下的所有文件--非递归
//    QStringList list = get_path_from_conf();

//    QStringList l1;
//    QStringList l2;



//    int in = 2;

//    out<<"文件："<<list[in];
//    make_rules(list[in],l1,l2);//从单个文件中解析出匹配规则列表

//    int inl = 8;
//    QString s1 = l2[inl];

//    out<<"第几行："<<s1;
//    QStringList li = rules_to_files(s1);//从单个规则中扫描出符合条件的路径

////    for(auto a:li)
////    {
////        out<<a;
////    }
//    out<<"结果数量: "<<li.size();





//    inl = 5;
//    s1 = l2[inl];

//    out<<"第几行："<<s1;
//    li = rules_to_files(s1);


////    for(auto a:li)
////    {
////        out<<a;
////    }
//    out<<"结果数量: "<<li.size();




//    inl = 9;
//    s1 = l2[inl];

//    out<<"第几行："<<s1;
//    li = rules_to_files(s1);


//    for(auto a:li)
//    {
//        out<<a;
//    }
//    out<<"结果数量: "<<li.size();


}

void qt_rules::set_path_conf(QString path)
{
    v_path_conf = path;
}

QStringList qt_rules::get_path_from_conf()
{
    QStringList list;

    if(v_path_conf.isEmpty() == false)
    {
        list = get_files_name(v_path_conf,false);
    }

    return list;
}

bool qt_rules::make_rules
    (QString path,QStringList &list_info,QStringList &list_path)
{
    QStringList list_all;
    int index_info = -1;
    int index_path = -1;
    int count = 0;

    //读取配置文件
    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        while(file.atEnd() == false)
        {
            QString str = file.readLine();

            //不为空加入内容
            if(str != "\n")
            {
                str = str.section("\n",0,0);
                list_all<<str;

                //拿到配置文件内容分段索引
                if(index_info == -1 && str == "[info]")
                {
                    index_info = count;
                }
                else if(index_path == -1 && str == "[path]")
                {
                    index_path = count;
                }

                count++;
            }
        }
        file.close();

        //返回容器
        list_info = QStringList(list_all.begin() + index_info + 1,
                                list_all.begin() + index_path);

        list_path = QStringList(list_all.begin() + index_path + 1,
                                list_all.end());

        return true;
    }
    else return false;//文件打开失败
}

QStringList qt_rules::rules_to_files(QString str_rules)
{
    QStringList list;

    QString str_op = str_rules.section("##",0,0);
    QString str_regex = str_rules.section("##",1,1);

    if(str_op.isEmpty() || str_regex.isEmpty()) return list;

    //检测正则表达式高级操作--处理结束后立即退出
    if(str_op == "-A")
    {
        QString a_path = str_regex;
        QString a_regex = str_rules.section("##",2,2);

        QStringList a_list = get_files_name(a_path);

        //从所有文件中匹配文件路径--加入到最终结果
        for(int i=0;i<a_list.size();i++)
        {
            //参数1:匹配规则
            //参数2:区分大小写(目前不区分)
            //参数3:支持通配符(目前支持,默认不支持)
            QRegExp rx(a_regex,Qt::CaseInsensitive,QRegExp::Wildcard);

            bool is_ok = rx.exactMatch(a_list[i]); //完全匹配返回true
            if(is_ok) list<<a_list[i];//加入到最终结果
        }

        return list;
    }

    //解析出环境变量
    if(str_regex.contains("%"))
    {
        QString str_temp = str_regex.section("%",1,1);

        //linux API
        string temp = str_temp.toStdString();
        string env = getenv(temp.c_str());

        //获取到正则表达式
        str_regex = str_regex.section("%",2,2);
        str_regex = QString::fromStdString(env) + str_regex;
    }

    //如果是可变路径,则从相同根路径开始扫描可匹配路径
    bool is_variable_path = false;//路径可变
    if(find_flg(str_regex.section("/",0,-2)) != -1) is_variable_path = true;

    //扫描文件--包括递归和不递归，支持可变目录
    if(str_op == "-f" || str_op == "-r")
    {
        //匹配路径
        QString path_regex = str_regex.section("/",0,-2);

        //扫描的可匹配路径
        QStringList list_dir_regex = get_regex_dir(path_regex,is_variable_path);

        //是否递归进入目录
        bool is_into_dir = false;
        if(str_op == "-r") is_into_dir = true;

        //从所有文件中匹配文件路径--最终结果
        list = get_regex_func(&get_files_name,list_dir_regex,str_regex,is_into_dir);

        show_arr<QStringList>(list_dir_regex,"可匹配的路径");
    }

    //扫描文件夹--包括递归和不递归，支持可变目录
    else if(str_op == "-R")
    {
        //匹配路径
        QString path_regex = str_regex.section("/",0,-2);

        //扫描的可匹配路径
        QStringList list_dir_regex = get_regex_dir(path_regex,is_variable_path);

        //从所有文件中匹配文件路径--最终结果
        list = get_regex_func(&get_path_dir,list_dir_regex,str_regex,false);

        show_arr<QStringList>(list_dir_regex,"可匹配的路径");
    }

    return list;
}

int qt_rules::find_flg(QString str)
{
    int count = -1;

    if(str.contains("*") || str.contains("?"))
    {
        count = 0;
        for(int i=0;i<str.size();i++)
        {
            if(str[i] == '/') count++;
            if(str[i] == '*') break;
        }
    }

    return count;
}

QStringList qt_rules::split_file(QString path, QString flg)
{
    QStringList list;

    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        QString str = file.readLine();
        str = str.section(flg,0,-2);
        list = str.split(flg,QString::SkipEmptyParts);
        file.close();
    }

    return list;
}

int qt_rules::split_pos(const QStringList &list,
        QString &str_find,QString &str_content,QString flg)
{
    int pos = -1;
    for(int i=0;i<list.size();i++)
    {
        if(list[i] == str_find.section(flg,0,0))
        {
            str_content = str_find.section(flg,1,1);
            pos = i;
            break;
        }
    }

    return pos;
}

//获取文件名
QStringList qt_rules::get_files_name(QString path,bool is_into)
{
    QStringList list;

    QFileInfoList list_info = get_files_info(path,is_into);
    for(int i=0;i<list_info.size();i++)
    {
        QFileInfo info(list_info[i]);
        list<<info.absoluteFilePath();
    }

    return list;
}

QStringList qt_rules::get_path_dir(QString path, bool is_into)
{
    QStringList list_dir;

    QDir dir(path);
    QFileInfoList list_dir_i = dir.entryInfoList
            (QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i != list_dir_i.size(); i++)
    {
        QString abs = list_dir_i[i].absoluteFilePath();
        list_dir += abs;
        if(is_into) list_dir += get_path_dir(abs);
    }

    return list_dir;
}

//获取文件全部信息
QFileInfoList qt_rules::get_files_info(QString path,bool is_into)
{
    QDir dir(path);
    QFileInfoList list_file = dir.entryInfoList
            (QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList list_dir = dir.entryInfoList
            (QDir::Dirs | QDir::NoDotAndDotDot);

    if(is_into)
    {
        for(int i = 0; i != list_dir.size(); i++)
        {
             QString name = list_dir.at(i).absoluteFilePath();
             QFileInfoList child_file_list = get_files_info(name);
             list_file.append(child_file_list);
        }
    }

    return list_file;
}

QStringList qt_rules::get_regex_dir(QString path_regex,bool is_variable)
{
    //扫描的可匹配路径
    QStringList list_dir_regex;

    //路径可变状态--扫描所有匹配路径
    if(is_variable)
    {
        //获取扫描根路径下的所有目录--搜索路径
        int index_find = find_flg(path_regex);
        QString path_search = path_regex.section("/",0,index_find - 1);
        QStringList list_dir_search =  get_path_dir(path_search);

        //从搜索路径中扫描出匹配的路径
        for(int i=0;i<list_dir_search.size();i++)
        {
            //参数1:匹配规则
            //参数2:区分大小写(目前不区分)
            //参数3:支持通配符(目前支持,默认不支持)
            QRegExp rx(path_regex,Qt::CaseInsensitive,QRegExp::Wildcard);

            bool is_ok = rx.exactMatch(list_dir_search[i]); //完全匹配返回true
            if(is_ok) list_dir_regex<<list_dir_search[i];
        }
    }
    else list_dir_regex<<path_regex;//固定路径，直接加入

    return list_dir_regex;
}

//QStringList qt_rules::get_regex_files
//    (QStringList list_dir_regex,QString str_regex, bool is_into_dir)
//{
//    QStringList list_path_result;

//    //从匹配路径中扫描所有文件
//    QStringList list_path_all;
//    for(int i=0;i<list_dir_regex.size();i++)
//    {
//        list_path_all += get_files_name(list_dir_regex[i],is_into_dir);
//    }

//    //从所有文件中匹配文件路径--加入到最终结果
//    for(int i=0;i<list_path_all.size();i++)
//    {
//        //参数1:匹配规则
//        //参数2:区分大小写(目前不区分)
//        //参数3:支持通配符(目前支持,默认不支持)
//        QRegExp rx(str_regex,Qt::CaseInsensitive,QRegExp::Wildcard);

//        bool is_ok = rx.exactMatch(list_path_all[i]); //完全匹配返回true
//        if(is_ok) list_path_result<<list_path_all[i];//加入到最终结果
//    }

//    return list_path_result;
//}

//QStringList qt_rules::get_regex_dir(QStringList list_dir_regex, QString str_regex, bool is_into_dir)
//{
//    QStringList list_path_result;

//    //从匹配路径中扫描所有文件
//    QStringList list_path_all;
//    for(int i=0;i<list_dir_regex.size();i++)
//    {
//        list_path_all += get_path_dir(list_dir_regex[i],is_into_dir);
//    }

//    //从所有文件中匹配文件路径--加入到最终结果
//    for(int i=0;i<list_path_all.size();i++)
//    {
//        //参数1:匹配规则
//        //参数2:区分大小写(目前不区分)
//        //参数3:支持通配符(目前支持,默认不支持)
//        QRegExp rx(str_regex,Qt::CaseInsensitive,QRegExp::Wildcard);

//        bool is_ok = rx.exactMatch(list_path_all[i]); //完全匹配返回true
//        if(is_ok) list_path_result<<list_path_all[i];//加入到最终结果
//    }

//    return list_path_result;

//}

QStringList qt_rules::get_regex_func
    (QStringList (*ptr_func)(QString, bool),
     QStringList list_dir_regex,
     QString str_regex, bool is_into_dir)
{

    QStringList list_path_result;

    //从匹配路径中扫描所有文件
    QStringList list_path_all;
    for(int i=0;i<list_dir_regex.size();i++)
    {
        list_path_all += ptr_func(list_dir_regex[i],is_into_dir);
    }

    //从所有文件中匹配文件路径--加入到最终结果
    for(int i=0;i<list_path_all.size();i++)
    {
        //参数1:匹配规则
        //参数2:区分大小写(目前不区分)
        //参数3:支持通配符(目前支持,默认不支持)
        QRegExp rx(str_regex,Qt::CaseInsensitive,QRegExp::Wildcard);

        bool is_ok = rx.exactMatch(list_path_all[i]); //完全匹配返回true
        if(is_ok) list_path_result<<list_path_all[i];//加入到最终结果
    }

    return list_path_result;
}

