#include "biometrickeyboardmodel.h"

#include <QFileInfoList>
#include <QGuiApplication>
#include <QStringList>
#include <QQmlApplicationEngine>
#include <QApplication>

#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>



/*
   This example illustrates exposing a QStringList as a
   model in QML
*/

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);

    QString rootHome = "/home/daniil";


    BiometricKeyboardModel * biometricModel= new BiometricKeyboardModel();

    //qmlRegisterType("fm" ,1,0, FileManagerModel);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("biometricModel", biometricModel);
    engine.load(QUrl(QStringLiteral("qrc:/mainTaper.qml")));


    return app.exec();
}
