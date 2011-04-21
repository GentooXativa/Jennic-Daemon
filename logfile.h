#ifndef LOGFILE_H
#define LOGFILE_H

#include <QObject>
#include <QSettings>
#include <QtCore>
#include <QTextStream>
#include <QFile>

class LogFile : public QObject
{
    Q_OBJECT
public:
    LogFile(QObject *parent = 0)
    {};

    ~LogFile()
    {};

    static inline bool writeLog( QString packet )
    {
        QStringList dpacket = packet.split(";");

        QSettings settings;

        QString dir = settings.value("data_directory").toString();

        if( dpacket.size() >= 5 )
        {
            qDebug() << "Hay mas parametros de lo esperado. (" << dpacket.size() << ")";

            QString filename( QString( "%1/packet.raw" ).arg(dir));

            QFile file( filename );

            if( !file.exists())
            {
                qDebug() << "No se ha encontrado el archivo " << dir << "/packet.raw creandolo.";
            }

            if (!file.open(QIODevice::ReadWrite | QIODevice::Append))
            {
                qDebug() << "No se ha podido escribir en el archivo.";
                return false;
            }

            file.write(QDateTime::currentDateTime().toString(Qt::LocaleDate).toStdString().c_str(), qstrlen(QDateTime::currentDateTime().toString(Qt::LocaleDate).toStdString().c_str()) );
            file.write(packet.toStdString().c_str(), qstrlen(packet.toStdString().c_str()));
            file.close();

            return false;
        }

        QVariant mac = qVariantFromValue( dpacket.at(0) );
        QVariant luz = qVariantFromValue( dpacket.at(1) );
        QVariant temperatura = qVariantFromValue( dpacket.at(2) );
        QVariant humedad = qVariantFromValue( dpacket.at(3) );

        QString filename( QString( "%1/%2.dat" ).arg(dir).arg(mac.toString()));

        QFile file( filename );

        if( !file.exists())
        {
            qDebug() << "No se ha encontrado el archivo " << mac.toString() << ".dat creandolo.";
        }

        if (!file.open(QIODevice::ReadWrite | QIODevice::Append))
        {
            qDebug() << "No se ha podido escribir en el archivo.";
            return false;
        }

        QString out(
                QString( "%1 - Mac: %2 - Luz: %3 - Temp: %4 - Humedad: %5%\n\r" )
                .arg( QDateTime::currentDateTimeUtc().toString(Qt::LocaleDate) )
                .arg( mac.toString() )
                .arg( luz.toInt()  )
                .arg( temperatura.toInt() )
                .arg( humedad.toInt() ));

        qDebug() << "Ping" << "- " << out.toStdString().c_str();
        file.write(out.toStdString().c_str(), qstrlen(out.toStdString().c_str()));
        file.close();
        return true;
        };

signals:

public slots:

};

#endif // LOGFILE_H
