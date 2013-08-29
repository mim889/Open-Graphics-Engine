#include "errorlog.h"

OGE::ErrorLOG::ErrorLOG() : err_file("err.log"),err_stream(&err_file)
{
    err_file.open(QIODevice::WriteOnly);
}
OGE::ErrorLOG::~ErrorLOG()
{
    err_file.close();
}
