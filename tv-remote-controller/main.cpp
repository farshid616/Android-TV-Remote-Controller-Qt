#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "remotecontrolcore.h"
#include "keycodesenum.h"
int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    KeyCodes::KeysCodeQMLDeclaration();
//    qmlRegisterType<KeyCodes>("KeyCodes", 1, 0, "KeyCodes");
    qmlRegisterType<RemoteControlCore>("RemoteController", 1, 0, "RemoteController");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

//    RemoteControlCore remote_core;
    return app.exec();
}
