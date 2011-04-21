/*
 * Copyright 2011 Heidi Martinez Kempff-Andersen
 *
 * This file is part of jennicDaemon.
 *
 * jennicDaemon is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * jennicDaemon is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with jennicDaemon. If not, see http://www.gnu.org/licenses/.
 */
#include <QtSql>
#include <QtCore>
#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "abstractserial.h"
#include <windows.h>
#include <qtimer.h>
#include <math.h>

#include "databaseexplorer.h"

#include "logfile.h"
#include "nodeoverview.h"
#include "portselection.h"

#define PI (3.141592653589793)

/**** Declaració de variables Globals: **************/
    QTimer* Timer0;
/****************************************************/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_gotError = false;
    ui->setupUi(this);

    // Creamos el icono de la bandeja del sistema
    createSystemTray();
    log("Iniciando base de datos.");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("storage.db");

    if( !db.open())
    {
        log("No se ha podido abrir la base de datos SQLite!");
        QMessageBox::critical(0, tr("No se puede abrir la base de datos"), tr("No se puede conectar a la base de datos.\nComprueba que tienes el soporte de SQLite!"), QMessageBox::Cancel);
    }else
    {
        log("Se ha abierto la base de datos SQLite!");
    }

    systemTray->showMessage("Aplicacion iniciada!", "La aplicacion se ha iniciado correctamente.", QSystemTrayIcon::Information, 2000);

    systemTray->showMessage("Aplicacion iniciada!", "La aplicacion se ha iniciado correctamente.", QSystemTrayIcon::Information, 2000);

    QSettings settings;

    if( settings.value("data_directory").toString() == "" )
    {

        QMessageBox::information(this, "Atencion", "Debes elegir un directorio donde guardar los\n\rarchivos de datos de los nodos.", QMessageBox::Ok);
        QFileDialog *file = new QFileDialog(this, "Elige un directorio para guardar los datos.", "C:" );
        file->setFileMode(QFileDialog::Directory);

        QString dir = file->getExistingDirectory();

        settings.setValue("data_directory", qVariantFromValue(dir));
    }

    if( settings.value("port").toString() == "" )
    {
        QMessageBox::information(this, "Atencion", "Debes elegir un puerto serie para empezar a recolectar\n\rlos datos.", QMessageBox::Ok);


    }

    NodeOverview *nodeo = new NodeOverview(this);

    connect( this, SIGNAL(dataReceived(QString,int,int,int)), nodeo, SLOT(setData(QString,int,int,int)));
    setCentralWidget(nodeo);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void MainWindow::Bucle()
{
    /*
    Timer0->stop();

    char buffin[11000];

    qint64 numBytes;
    qint64 i = -1;

    bool bError = 1;


    for (i=0;i<1024;i++)
        buffin[i]=0;

    i = -1;


    numBytes = portserie->bytesAvailable();
    int tbytes = numBytes;

    if(numBytes > 11000)
        numBytes = 11000;

    if (portserie->isOpen())
    {
        i = portserie->read(buffin, numBytes);

        log( QString("DEBUG - Bytes availables: %1 - Bytes leidos: %2").arg(tbytes ).arg(i) );
        log( QString("DEBUG - Port Size: %1").arg(portserie->size()));

        if( i > tbytes )
            return;

        if (!(i>-1))
            portserie->close();
        else if (i>0)
        {
            bError = 0;
        }
    }

    if (i > 0)
    {
        buffin[i]='\0';
        if( i >= 1 )
        {
            //log(QString("%1").arg(buffin));
            LogFile::writeLog(buffin);
            parsePacket(QString(buffin));
        }
    }

    Timer0->start(1000);*/
}

void MainWindow::createSystemTray()
{
    log("Creando el icono de la bandeja del sistema.");
    systemTray = new QSystemTrayIcon(this);
    systemTray->setIcon(QIcon(":/images/actions/images/app_icon.png"));
    systemTray->show();

    log("Comprobando configuracion del puerto.");

    QSettings settings;

    if( settings.value("current/port").toString().isEmpty() )
    {
        log("No se ha encontrado la configuracion por defecto.");
        QMessageBox::warning(this, "Error", "No se ha encontrado la configuracion para el puerto.\n\rPor favor, revise la configuracion.", QMessageBox::Yes );
        on_actionConfigurar_puerto_triggered();
    }
    else
    {
        log(QString("Cargando configuracion para el puerto %1").arg(settings.value("current/port").toString()));
    }
}

void MainWindow::on_actionSalir_triggered()
{
    // Empezamos el cierre del programa
    log("Cerrando la aplicacion.");
    // Al finalizar cerramos la ventana y se dispara el LastWindowClosed
    close();
}

void MainWindow::on_actionConfigurar_puerto_triggered()
{
}

void MainWindow::log(QString txt)
{
    //ui->textEdit->append( QString( "%1 - %2").arg( QDateTime::currentDateTime().toString(Qt::LocaleDate)).arg( txt ));
    ui->plainTextEdit->appendPlainText(QString( "%1 - %2").arg( QDateTime::currentDateTime().toString(Qt::LocaleDate)).arg( txt ));
}

void MainWindow::on_actionExplorador_Base_de_Datos_triggered()
{

}

void MainWindow::on_actionAbrir_Puerto_triggered()
{
    /*1. First - create an instance of an object.*/
    port = new AbstractSerial(this);

    /*2. Second - set the device name.*/
    QString dn("COM4"); //device name

   // dn = ui->lineEdit_puerto->text();
    port->setDeviceName(dn);

    connect(port, SIGNAL(readyRead()), this, SLOT(transaction()));

    /* 3. Third - open the device.*/
    if (port->open(AbstractSerial::ReadOnly | AbstractSerial::Unbuffered)) {
        ui->plainTextEdit->appendPlainText(QString("Serial Device %1 open in %2").arg(port->deviceName()).arg(port->openMode()));

        //Here, the default current parameters (for example)
        ui->plainTextEdit->appendPlainText(QString("= Default parameters ="));
        ui->plainTextEdit->appendPlainText(QString("Device Name %1").arg(port->deviceName()));
        ui->plainTextEdit->appendPlainText(QString("Baud Rate %1").arg(port->baudRate()));
        ui->plainTextEdit->appendPlainText(QString("Data bits %1").arg(port->dataBits()));
        ui->plainTextEdit->appendPlainText(QString("Parity %1").arg(port->parity()));
        ui->plainTextEdit->appendPlainText(QString("Stop bits %1").arg(port->stopBits()));
        ui->plainTextEdit->appendPlainText(QString("Flow %1").arg(port->flowControl()));
        ui->plainTextEdit->appendPlainText(QString("Total read timeout constant,msec %1").arg(port->totalReadConstantTimeout()));
        ui->plainTextEdit->appendPlainText(QString("Char interval timeout,usec %1").arg(port->charIntervalTimeout()));

        /* 4. Fourth - now you can set the parameters. (after successfully opened port)
        */

        //Here example set baud rate 115200 bit/sec (baud)
        if (!port->setBaudRate(AbstractSerial::BaudRate115200)) {
            ui->plainTextEdit->appendPlainText(QString("Set baud rate %1 error").arg(AbstractSerial::BaudRate115200));
            return;
        };

        if (!port->setDataBits(AbstractSerial::DataBits8)) {
            ui->plainTextEdit->appendPlainText(QString("Set data bits %1 error").arg(AbstractSerial::DataBits8));
            return;
        }

        if (!port->setParity(AbstractSerial::ParityNone)) {
            ui->plainTextEdit->appendPlainText(QString("Set parity %1 error").arg(AbstractSerial::ParityNone));
            return;
        }

        if (!port->setStopBits(AbstractSerial::StopBits1)) {
            ui->plainTextEdit->appendPlainText(QString("Set stop bits %1 error").arg(AbstractSerial::StopBits1));
            return;
        }

        if (!port->setFlowControl(AbstractSerial::FlowControlOff)) {
            ui->plainTextEdit->appendPlainText(QString("Set flow %1 error").arg(AbstractSerial::FlowControlOff));
            return;
        }
        if (port->openMode() & AbstractSerial::Unbuffered){
            port->setTotalReadConstantTimeout(10);
        }
        //Here, the default current parameters (for example)
        ui->plainTextEdit->appendPlainText(QString("= New parameters ="));
        ui->plainTextEdit->appendPlainText(QString("Device Name %1").arg(port->deviceName()));
        ui->plainTextEdit->appendPlainText(QString("Baud Rate %1").arg(port->baudRate()));
        ui->plainTextEdit->appendPlainText(QString("Data bits %1").arg(port->dataBits()));
        ui->plainTextEdit->appendPlainText(QString("Parity %1").arg(port->parity()));
        ui->plainTextEdit->appendPlainText(QString("Stop bits %1").arg(port->stopBits()));
        ui->plainTextEdit->appendPlainText(QString("Flow %1").arg(port->flowControl()));
        ui->plainTextEdit->appendPlainText(QString("Total read timeout constant,msec %1").arg(port->totalReadConstantTimeout()));
        ui->plainTextEdit->appendPlainText(QString("Char interval timeout,usec %1").arg(port->charIntervalTimeout()));
    }

}

void MainWindow::on_actionKernelTest_triggered()
{
    parsePacket("001122334455667788;1;32;42");
}

void MainWindow::parsePacket(QString pck )
{
    QString m_mac = QString("");

    int m_temp, m_humi, m_light = 0;

    QStringList packet = pck.split(";");

    if( packet.size() <= 4 )
    {
        if( m_gotError )
        {
             QMessageBox::critical(this, "Error critico", QString( "Ha habido mas de un fallo en el parseo de las tramas.\n\rCerrando la aplicacion.\n\rSe han encontrado %1 parametros, se esperaban 4 :)").arg(packet.size()), QMessageBox::Ok );
             close();
        }

        QMessageBox::critical(this, "Error critico", QString( "Se han encontrado %1 parametros, se esperaban 4 :)").arg(packet.size()), QMessageBox::Ok );
        m_gotError = true;

        return;
    }

    m_mac = packet.at(0);
    m_temp = qVariantFromValue(packet.at(1)).toInt();
    m_humi = qVariantFromValue(packet.at(2)).toInt();
    m_light = qVariantFromValue(packet.at(3)).toInt();

    emit dataReceived(m_mac, m_temp, m_humi, m_light );

    return;
}

void MainWindow::transaction()
{
    QByteArray data = port->readAll();
    ui->plainTextEdit->appendPlainText(QString("Readed: %1 bytes").arg(data.size()));
    ui->plainTextEdit->appendPlainText(QString("%1 ").arg(QString(data)));
}

