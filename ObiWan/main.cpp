#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWidgets>
#include "obiwanapplication.h"
#include "sqliteconnection.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    ObiWanApplication app(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    if (!createConnection(&db)) return 1;
    QSqlTableModel model(&app, db);
    model.setTable("job");
/*
    model.setHeaderData(0, Qt::Horizontal, tr("id"));
    model.setHeaderData(1, Qt::Horizontal, tr("name"));
    model.setHeaderData(2, Qt::Horizontal, tr("height"));
*/
    cout << "Select: " << model.select() << endl;

    cout << "Row count: " << model.rowCount() << endl;

    app.initDb(&model, db);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("app", &app);
    engine.rootContext()->setContextProperty("jobs_model", &model);
    engine.load(url);

    app.exec();
    app.terminate();
    return 0;
}
