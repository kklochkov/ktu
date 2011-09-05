#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "importer.h"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QThread worker;

    Importer importer;
    importer.moveToThread(&worker);

    QObject::connect(&worker, SIGNAL(started()), &importer, SLOT(import()));
    QObject::connect(&importer, SIGNAL(finished()), &worker, SLOT(quit()));
    QObject::connect(&worker, SIGNAL(finished()), &app, SLOT(quit()));

    if (!importer.openMDB("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=C:/KTU/Bd_nv.mdb")) {
        qDebug() << Q_FUNC_INFO << importer.lastError();
        return 0;
    }

    worker.start();

    return app.exec();
}
