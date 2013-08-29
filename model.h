#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QVector>
#include <QVector3D>
#include <QVector2D>

#include <QFile>
#include <QTextStream>

#include <QDebug>
#include <QGLBuffer>
#include <QGLShaderProgram>
namespace OGE
{
class Model
{
public:
    Model();
    ~Model();
    void Load_OBJ(QString file_name,QString file_name_mtl);
    void Draw(QGLShaderProgram & shaderProgram, QMatrix4x4 pMatrix,QMatrix4x4 vMatrix, QMatrix4x4 mMatrix, QVector3D LightPosition);

private:
    unsigned int vertexCount;
    QGLBuffer *buffer;
};
}
#endif // MODEL_H
