#ifndef CHARTSTEST_H
#define CHARTSTEST_H

#include <QMainWindow>
#include <QLineSeries>
#include <QBarSet>

namespace Ui {
class ChartsTest;
}

class ChartsTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChartsTest(QWidget *parent = nullptr);
    ~ChartsTest();
    void initLineChart();
    void initBarChart();
    void reloadLineData();
    void reloadBarData();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChartsTest *ui;

    QLineSeries *m_line;
    QBarSet     *m_barSet;   // 柱状图的一组柱子
};

#endif // CHARTSTEST_H
