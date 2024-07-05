#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include<QPainter>

namespace Ui{
class Clock;
}

class Clock : public QWidget
{
    Q_OBJECT
public:
    explicit Clock(QWidget *parent = nullptr);
    ~Clock();
    void paintEvent(QPaintEvent *event);

private:
     Ui::Clock *ui;

signals:

};

#endif // CLOCK_H
