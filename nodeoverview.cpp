#include <QTimer>
#include <QDateTime>
#include "nodeoverview.h"
#include "ui_nodeoverview.h"

NodeOverview::NodeOverview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NodeOverview)
{
    ui->setupUi(this);

    temp = new ThermoMeter(this);

    temp->setMaximum(100);
    temp->setMinimum(-20);

    temp->setCritical(50);
    temp->setNominal(30);

    temp->setValue(16);
    temp->setSuffix("ºC");

    humi = new ManoMeter(this);

    humi->setMaximum(100);
    humi->setMinimum(0);

    humi->setCritical(90);
    humi->setNominal(75);

    humi->setSuffix("% Hum");

    ui->layout_temperatura->addWidget(temp, 1);
    ui->layout_humedad->addWidget(humi, 1);

    ui->label_mac->setText( "Esperando informacion del nodo...");
}

NodeOverview::~NodeOverview()
{
    delete ui;
}

void NodeOverview::setData(QString m_mac, int m_temp, int m_humi, int m_light)
{
    ui->label_mac->setText( QString( "MAC: %1 - Ultimo informe: %2").arg(m_mac).arg( QDateTime::currentDateTime().toString(Qt::LocaleDate)));
    temp->setValue(m_temp);
    humi->setValue(m_humi);
    ui->progressBar->setValue(m_light);
}
