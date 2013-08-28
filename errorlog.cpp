#include "errorlog.h"

ErrorLOG::ErrorLOG() : err_file("err.log"),err_stream(&err_file)
{
    err_file.open(QIODevice::WriteOnly);
}
ErrorLOG::~ErrorLOG()
{
    err_file.close();
}
