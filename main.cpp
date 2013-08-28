#include "mainwindow.h"
#include "errorlog.h"
#include <QApplication>
#include <QtGlobal>
#define ERRORLOG 1
#if ERRORLOG == 1
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        ErrorLOG::getSingleton() << "Debug: " << localMsg.constData() << " File: " <<  context.file << " in line " << context.line << " in function " << context.function << "\n";
        break;
    case QtWarningMsg:
        ErrorLOG::getSingleton() << "Warning: " << localMsg.constData() << " File: " <<  context.file << " in line " << context.line << " in function " << context.function << "\n";
        break;
    case QtCriticalMsg:
        ErrorLOG::getSingleton() << "Critical: " << localMsg.constData() << " File: " <<  context.file << " in line " << context.line << " in function " << context.function << "\n";
        break;
    case QtFatalMsg:
        QFile file("err.log");
        QTextStream err_stream(&file);
        file.open(QIODevice::WriteOnly);
        err_stream << "Fatal: " << localMsg.constData() << " File: " <<  context.file << " in line " << context.line << " in function " << context.function << "\n";
        file.close();
        abort();
    }
}
#endif

int main(int argc, char *argv[])
{
    #if ERRORLOG == 1
       qInstallMessageHandler(myMessageOutput);
    #endif
       qDebug() << "debuguje";
       qCritical() << "critical ;/";
       qFatal("huj1");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
