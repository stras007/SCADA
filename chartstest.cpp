#include "chartstest.h"
#include "ui_chartstest.h"
#include <QValueAxis>
#include <QRandomGenerator>
#include <QBarSeries>
#include <QBarCategoryAxis>


ChartsTest::ChartsTest(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChartsTest)
{
    ui->setupUi(this);
    //初始化折线图
    this->initLineChart();
    this->initBarChart();
    //初始化数据
    reloadLineData();
    reloadBarData();
}

ChartsTest::~ChartsTest()
{
    delete ui;
}

void ChartsTest::initLineChart()
{
    //1.准备一个QChart
    QChart *chart = new QChart;
    chart->setTitle(QStringLiteral("一周最高气温"));
    chart->legend()->hide();
    //透明背景色
    chart->setBackgroundVisible(false);

    this->m_line = new QLineSeries;
    //设置名字
    this->m_line->setName(QStringLiteral("气温"));
    //设置折线的颜色 粗细
    this->m_line->setPen(QPen(QColor("#0d9488"), 2));
    this->m_line->setPointsVisible(true);
    chart->addSeries(m_line);

    //绘制X轴
    QValueAxis *aixX = new QValueAxis;
    aixX->setRange(1,7);
    aixX->setTickCount(7);
    aixX->setLabelFormat("%.0f");
    aixX->setTitleText(QStringLiteral("星期"));
    //放到chart  放到下面就是x轴
    chart->addAxis(aixX,Qt::AlignBottom);
    this->m_line->attachAxis(aixX);
    //绘制Y轴
    QValueAxis *aixY = new QValueAxis;
    aixY->setRange(0,40);
    aixY->setLabelFormat("%.0f");
    aixY->setTitleText(QStringLiteral("°C"));
    //放到chart  放到下面就是x轴
    chart->addAxis(aixY,Qt::AlignLeft);
    this->m_line->attachAxis(aixY);
    //在界面的显示框里
    ui->lineView->setChart(chart);
}

void ChartsTest::initBarChart()
{
    //1.准备一个QChart
    QChart *chart = new QChart;
    chart->setTitle(QStringLiteral("各科成绩"));
    chart->legend()->hide();
    //透明背景色
    chart->setBackgroundVisible(false);

    //设置柱状图柱子
    // 一组柱子 = 一个 QBarSet，set 里 append 几个值就画几根柱
    m_barSet = new QBarSet(QStringLiteral("成绩"));
    m_barSet->setColor(QColor("#0d9488"));
    m_barSet->setBorderColor(QColor("#0f172a"));   // 柱子描边，白底上边界更清楚

    QBarSeries *series = new QBarSeries;
    series->append(m_barSet);
    series->setLabelsVisible(true);//显示数值
    chart->addSeries(series);

    //x轴 - 字符串类型
    QBarCategoryAxis *aixX = new QBarCategoryAxis;
    aixX->setCategories({QStringLiteral("语文"), QStringLiteral("数学"),
                         QStringLiteral("英语"), QStringLiteral("物理")});
    chart->addAxis(aixX,Qt::AlignBottom);
    series->attachAxis(aixX);


    QValueAxis *aixY = new QValueAxis;
    aixY->setRange(0,100);
    aixY->setLabelFormat("%.0f");
    //放到chart  放到下面就是x轴
    chart->addAxis(aixY,Qt::AlignLeft);
    series->attachAxis(aixY);

    ui->barView->setChart(chart);
}

void ChartsTest::reloadLineData()
{
    this->m_line->clear();//先清空折线图里面的数据
    for(int i=1;i<=7;i++){
        this->m_line->append(i,QRandomGenerator::global()->bounded(2,40));
    }
}

void ChartsTest::reloadBarData()
{
    QList<qreal> lists;
    for(int i = 0;i<4;i++)
        lists<< QRandomGenerator::global()->bounded(8,100);
    //添加数据之前 先清空原来的数据
    m_barSet->remove(0,lists.size());
    m_barSet->append(lists);
}

void ChartsTest::on_pushButton_clicked()
{
    this->reloadLineData();
    this->reloadBarData();
}

