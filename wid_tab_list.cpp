#include "wid_tab_list.h"

wid_tab_list::wid_tab_list(QWidget *parent) : QWidget(parent)
{
    //表格列--去除行列标题,隐藏滚动条,水平占满
    tab_list = new QTableWidget(this);
    tab_list->horizontalHeader()->setVisible(false);
    tab_list->verticalHeader()->setVisible(false);
    tab_list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tab_list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tab_list->horizontalHeader()->setStretchLastSection(true);

    //表格列--去除行列标题,隐藏滚动条,水平占满
    tab_title = new QTableWidget(this);
    tab_title->horizontalHeader()->setVisible(false);
    tab_title->verticalHeader()->setVisible(false);
    tab_title->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tab_title->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tab_title->horizontalHeader()->setStretchLastSection(true);

    //全选按钮
    butt_choose = new QPushButton(this);
    butt_choose->setText("全选");
    butt_choose->hide();

    //清空按钮
    butt_clear = new QPushButton(this);
    butt_clear->setText("清空");
    butt_clear->hide();

    //初始化默认列表半透明背景
    col_content = QColor(127,127,127,127);

    //反选信号
    connect(butt_choose,&QPushButton::clicked,this,[=](){


        if(tab_list != nullptr)
        {
            if(tab_list->rowCount() > 0)
            {
                Qt::CheckState status = Qt::Checked;
                if(tab_list->item(0,0)->checkState() == Qt::Checked)
                    status = Qt::Unchecked;

                for(int i=0;i<tab_list->rowCount();i++)
                {
                    tab_list->item(i,0)->setCheckState(status);
                }
                emit fa_press_choose();
            }
        }
    });

    //清空信号
    connect(butt_clear,&QPushButton::clicked,this,[=](){

        if(tab_list != nullptr)
        {
            if(tab_list->rowCount() > 0)
            {
                tab_list->clear();
                tab_list->setRowCount(0);
                tab_list->setColumnCount(0);
                emit fa_press_clear();
            }
        }
    });

}

void wid_tab_list::set_title(QString title, QColor col)
{
    this->set_size(this->size().width(),size_wide);

    //添加表格行列
    tab_title->setColumnCount(1);
    tab_title->setRowCount(1);

    //将标题放入表格中
    QTableWidgetItem *temp = new QTableWidgetItem;
    temp->setText(title);
    temp->setTextAlignment(Qt::AlignCenter);
    temp->setFlags(Qt::NoItemFlags);
    tab_title->setItem(0,0,temp);

    //设置透明背景（需要自定义添加背景）
    QPalette palette;//QPalette::Base
    palette.setColor(QPalette::Base,col);
    tab_title->setPalette(palette);//设置画板
}

void wid_tab_list::set_content(QStringList list, QColor col)
{
    tab_list->setColumnCount(1);
    tab_list->setRowCount(list.size());

    //加内容,目前不支持其他列
    for(int i=0;i<list.size();i++)
    {
        QTableWidgetItem *temp = new QTableWidgetItem;
        temp->setText(list[i]);
        temp->setCheckState(Qt::Checked);
        temp->setFlags(temp->flags()&~Qt::ItemIsSelectable);//去除选中状态
        tab_list->setItem(i,0,temp);
    }
    col_content = col;
}

void wid_tab_list::set_size(int wide, int high,int space)
{
    v_space = space;

    this->resize(wide,high);
    this->show();
}

QVector<Qt::CheckState> wid_tab_list::get_status_vec()
{
    QVector<Qt::CheckState> vec_status;

    //查看打勾状态
    for(int i=0;i<tab_list->rowCount();i++)
    {
        if(tab_list->item(i,0)->checkState() == Qt::Checked)
            vec_status.push_back(Qt::Checked);
        else vec_status.push_back(Qt::Unchecked);
    }

    return vec_status;
}

void wid_tab_list::open()
{
    //设置透明背景（需要自定义添加背景）
    QPalette palette;//QPalette::Base
    palette.setColor(QPalette::Base,col_content);
    tab_list->setPalette(palette);//设置画

    tab_title->move(0,0);
    tab_title->resize(this->width(),size_wide);
    tab_title->show();

    tab_list->move(0,size_wide + v_space);
    tab_list->resize(this->size() - QSize(0,size_wide * 2 + v_space * 2));
    tab_list->show();

    butt_choose->move(0,this->height() - size_wide);
    butt_choose->resize(this->width()/2,size_wide);
    butt_choose->show();

    butt_clear->move(this->width()/2,this->height() - size_wide);
    butt_clear->resize(this->width()/2,size_wide);
    butt_clear->show();
}

void wid_tab_list::clear_list()
{
    emit this->fa_press_clear();
}

void wid_tab_list::open_choose(bool is_open,QColor col)
{
    if(is_open)
    {
        //设置透明背景（需要自定义添加背景）
        QPalette palette;//QPalette::Base
        palette.setColor(QPalette::Button,col);

        butt_choose->setFlat(true);
        butt_choose->setAutoFillBackground(true);
        butt_choose->setPalette(palette);//设置画

        butt_clear->setFlat(true);
        butt_clear->setAutoFillBackground(true);
        butt_clear->setPalette(palette);//设置画
    }
}
