#include "mainwindow.h"
#include "errorlog.h"
#include <QApplication>
#include <QtGlobal>
#include <QFile>
#include <QDebug>

#define ERRORLOG 1
#if ERRORLOG == 1   //1 -logowanie do pliku 0 - na konsole
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
    {
        QByteArray localMsg = msg.toLocal8Bit();
        switch (type)
        {
        case QtDebugMsg:
            OGE::ErrorLOG::getSingleton() << "Debug: " << localMsg.constData() << " File: " <<  context.file << " in line " << context.line << " in function " << context.function << "\n";
            break;
        case QtWarningMsg:
            OGE::ErrorLOG::getSingleton() << "Warning: " << localMsg.constData() << " File: " <<  context.file << " in line " << context.line << " in function " << context.function << "\n";
            break;
        case QtCriticalMsg:
            OGE::ErrorLOG::getSingleton() << "Critical: " << localMsg.constData() << " File: " <<  context.file << " in line " << context.line << " in function " << context.function << "\n";
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
    #elif (QT_VERSION <= QT_VERSION_CHECK(5, 0, 0))
        void myMessageOutput(QtMsgType type, const char *msg)
        {
            switch (type)
            {
                case QtDebugMsg:
                    OGE::ErrorLOG::getSingleton() << "Debug: " << msg;
                    break;
                case QtWarningMsg:
                    OGE::ErrorLOG::getSingleton() << "Warning: " << msg;
                    break;
                case QtCriticalMsg:
                    OGE::ErrorLOG::getSingleton() << "Critical: " << msg;
                    break;
                case QtFatalMsg:
                    QFile file("err.log");
                    QTextStream err_stream(&file);
                    file.open(QIODevice::WriteOnly);
                    err_stream << "Fatal: " << msg;
                    file.close();
                    abort();
                    break;
            }
        }
    #endif
#endif

int main(int argc, char *argv[])
{
    #if ERRORLOG == 1
        #if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
            qInstallMessageHandler(myMessageOutput);
        #elif (QT_VERSION <= QT_VERSION_CHECK(5, 0, 0))
            qInstallMsgHandler (myMessageOutput);
        #endif
    #endif

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
