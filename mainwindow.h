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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui {
    class MainWindow;
}

class AbstractSerial;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
    void createSystemTray();

signals:
    void    dataReceived( QString, int, int, int );

private:
    Ui::MainWindow *ui;
    AbstractSerial *port;

    QSystemTrayIcon *systemTray;
    bool        m_gotError;

private slots:
    void on_actionKernelTest_triggered();
    void on_actionAbrir_Puerto_triggered();
    void on_actionExplorador_Base_de_Datos_triggered();
    void on_actionConfigurar_puerto_triggered();
    void on_actionSalir_triggered();
    void log(QString);
    void Bucle();
    void parsePacket(QString);
    void transaction();

};

#endif // MAINWINDOW_H
