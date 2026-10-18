#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "SystemBridge.h"
#include "ShellController.h"
int main(int argc,char **argv){
 QGuiApplication app(argc,argv);
 app.setApplicationName("AstraShell");
 app.setQuitOnLastWindowClosed(false);
 SystemBridge system;
 ShellController shell;
 QObject::connect(&app,&QCoreApplication::aboutToQuit,&shell,&ShellController::restoreTaskbar);
 QQmlApplicationEngine engine;
 engine.rootContext()->setContextProperty("systemBridge",&system);
 engine.rootContext()->setContextProperty("shellController",&shell);
 engine.loadFromModule("AstraShell","Main");
 if(engine.rootObjects().isEmpty())return -1;
 return app.exec();
}
