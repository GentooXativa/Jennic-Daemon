#ifndef NODEOVERVIEW_H
#define NODEOVERVIEW_H

#include <QWidget>

#include <thermometer.h>
#include <manometer.h>

namespace Ui {
    class NodeOverview;
}

class NodeOverview : public QWidget
{
    Q_OBJECT

public:
    explicit NodeOverview(QWidget *parent = 0);
    ~NodeOverview();

protected slots:
    void    setData( QString mac, int temp, int humi, int light );

private:
    Ui::NodeOverview *ui;

    ThermoMeter *temp;
    ManoMeter   *humi;

};

#endif // NODEOVERVIEW_H
