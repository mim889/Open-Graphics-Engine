#ifndef ERRORLOG_H
#define ERRORLOG_H

#include <QDebug>
#include <QTextStream>
#include <QFile>
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


}
#endif // ERRORLOG_H
