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

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>

namespace OGE
{
class Model
{
public:
    Model();
    Model(QString file_name,QString file_name_mtl);
    ~Model();
    void Load_OBJ(QString file_name,QString file_name_mtl);
    void Load_Assimp(QString file_name);
    void Draw(QGLShaderProgram & shaderProgram, QMatrix4x4 pMatrix,QMatrix4x4 vMatrix, QMatrix4x4 mMatrix, QVector3D LightPosition);
    void Draw(QGLShaderProgram & shaderProgram, QMatrix4x4 pMatrix,QMatrix4x4 vMatrix, QVector3D LightPosition);
    void SetPosition(QVector3D pos);
    QVector3D GetPosition();

    void SetRotation(QVector3D roate);
    QVector3D GetRototion();
private:
    QVector3D position;
    QVector3D rotation;
    unsigned int vertexCount;
    QGLBuffer *buffer;

};
}
#endif // MODEL_H
