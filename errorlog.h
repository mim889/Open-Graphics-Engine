#ifndef ERRORLOG_H
#define ERRORLOG_H

#include <QDebug>
#include <QTextStream>
#include <QFile>
#define ERRORLOG 1
namespace OGE
{
class ErrorLOG
{
private:

    ErrorLOG();
    ~ErrorLOG();

    QFile err_file;
    QTextStream err_stream;

public:
    template < typename T >
    ErrorLOG & operator <<( const T & wypisz )
    {
        err_stream << wypisz;
        return * this;
    }
    static ErrorLOG & getSingleton()
    {
        static ErrorLOG singleton;
        return singleton;
    }


};
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
#elif (QT_VERSION <= QT_VERSION_CHECK(5, 0, 0))
    void myMessageOutput(QtMsgType type, const char *msg);
#endif

}
#endif // ERRORLOG_H
