#include "model.h"

OGE::Model::Model()
{
    vertexCount = 0;
}
OGE::Model::Model(QString file_name,QString file_name_mtl)
{
    Load_OBJ(file_name,file_name_mtl);
}
OGE::Model::~Model()
{

}

void OGE::Model::Load_OBJ(QString file_name,QString file_name_mtl)
{
    QString bufor;  //bufor do danych z QTextStream plików tekstowych
    QVector <QVector3D> vertices_tmp;       //tymczasowe wierzchołki
    QVector <QVector3D> normal_tmp;         //tymczasowe normalne
    QVector <QVector3D> color_vec;          //kolory dla każdego wierzchołka

    QVector <QVector3D> color_data_tmp;     //tymczasowe kolory wierzchołków
    QVector <QString> color_str;            //nazwy materiałów

    QVector <QVector2D> texture_coord_tmp;  //tymczasowe koordynanty tekstur
    QVector <QVector3D> triangles;          // w piliku obj jest f nr.wierzchołek/nr.tekstura/nr.normalna dlatego QVector3D.x to położenie, QVector3D.y to kolor, QVector3D.z to wektor normalny
    bool ColisionRead = false;
    QFile file_mtl(file_name_mtl);
    file_mtl.open(QIODevice::ReadOnly | QIODevice::Text);   //otwieramy plik *.mtl
    if(!file_mtl.isReadable())
    {
        qWarning() << "nie mozna czytac z pliku " << file_name_mtl;
    }
    QTextStream txtstr_mtl(&file_mtl);

    while(!txtstr_mtl.atEnd())          //czytanie mtl pliku
    {
        txtstr_mtl >> bufor;    //z QTextStream zapisujemy do bufora

        if(bufor == "newmtl")
        {
            txtstr_mtl >> bufor;
            color_str << bufor;     //nazwe koloru zapisujemy do vector color_str
            txtstr_mtl >> bufor;

            if(bufor == "Ka")           //ambient color
            {
                txtstr_mtl.readLine();
                txtstr_mtl >> bufor;
            }

            if(bufor == "Kd")           //kolor materiału (diffuse color)
            {
                float tmp_data = 0.5;
                QVector3D tmp_vec;
                txtstr_mtl >> tmp_data;
                tmp_vec.setX(tmp_data);

                txtstr_mtl >> tmp_data;
                tmp_vec.setY(tmp_data);

                txtstr_mtl >> tmp_data;
                tmp_vec.setZ(tmp_data);

                color_data_tmp << tmp_vec;

            }
        }
    }

    QFile file(file_name);                         //otwieranie pliku *.obj
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream txtstr(&file);
    if(!file.isReadable())
    {
        qWarning() << "nie mozna czytac z pliku " << file_name;
    }
    int color_index = 0;
    while(!txtstr.atEnd())              //czytanie pliku obj
    {
       txtstr >> bufor;
       if(bufor == "v")                 //trafiliśmy na v czyli wczytujemy wierzchołek
       {
           QVector3D tmp_vec;
           float tmp_data;

           txtstr >> tmp_data;
           tmp_vec.setX(tmp_data);

           txtstr >> tmp_data;
           tmp_vec.setY(tmp_data);

           txtstr >> tmp_data;
           tmp_vec.setZ(tmp_data);


           vertices_tmp << tmp_vec;

       }
       else if(bufor == "vt")       //vt czyli wektory teksturowe
       {
           QVector2D tmp_vec;
           float tmp_data;

           txtstr >> tmp_data;
           tmp_vec.setX(tmp_data);

           txtstr >> tmp_data;
           tmp_vec.setY(tmp_data);

           texture_coord_tmp << tmp_vec;
       }
       else if(bufor == "vn")       //vn czyli wektory normalne
       {
           QVector3D tmp_vec;
           float tmp_data;

           txtstr >> tmp_data;
           tmp_vec.setX(tmp_data);

           txtstr >> tmp_data;
           tmp_vec.setY(tmp_data);

           txtstr >> tmp_data;
           tmp_vec.setZ(tmp_data);

           normal_tmp << tmp_vec;
       }
       else if(bufor == "f" && !ColisionRead)        //trójkąty np 1/2/3 4/5/6 7/8/9 oznacza że wierzchołki trójkąta to 1,4,7 wektory teksturowe to 2,5,8, wektory normalne to 3,6,9
       {
           int tmp_data;
           QVector3D tmp_vec;
           char div;  // znak "/"

           for(int i =0;i<3;i++)
           {
                txtstr >> tmp_data;
                txtstr >> div;      // znak "/"
                tmp_vec.setX(tmp_data);

                txtstr >> tmp_data;
                txtstr >> div;      // znak "/"
                tmp_vec.setY(tmp_data);

                txtstr >> tmp_data;
                txtstr >> div;      // znak "/"
                tmp_vec.setZ(tmp_data);
                triangles << tmp_vec;
                color_vec << color_data_tmp[color_index];
           }

       }
       else if(bufor == "usemtl")           //zmieniamy materiał
       {
           QString color_name;
           txtstr >> color_name;
           if(color_name == "Collision" || color_name == "Colision" )
           {
               ColisionRead = true;
           }
           else
           {
               ColisionRead = false;
           }
           color_index = color_str.indexOf(color_name);

       }
    }
    QVector <QVector3D> vertices;       //wierzchołki
    QVector <QVector3D> normal;         //normalne
    QVector <QVector2D> texture_coord;  //koordynanty tekstur
    QVector <QVector3D> color;          //kolory wierzchołków
    for(int i =0; i < triangles.size();i++)         //finalne tworzenie "zbiorów" wierzchołków, kolorów wierzchołków, wektorów tekstur, wektorów normalnych
    {
        vertices << vertices_tmp[triangles[i].x()-1];
        color << color_vec[i];
        texture_coord << texture_coord_tmp[triangles[i].y()-1];
        normal << normal_tmp[triangles[i].z()-1];
    }
    vertices_tmp = vertices;
    color_vec = color;
    normal_tmp = normal;
    buffer = new QGLBuffer;
    buffer->create();
    buffer->bind();
    buffer->setUsagePattern(QGLBuffer::StaticDraw);
    buffer->allocate(vertices_tmp.size() * (3 + 3 + 3) * sizeof(GLfloat));      //3 współrzędne wierzchołków 3 składowe koloru i 3 składowe wektora normalnego
    int offset = 0;

    buffer->write(offset,vertices_tmp.constData(),vertices_tmp.size() * 3 * sizeof(GLfloat));
    offset += triangles.size() * 3 * sizeof(GLfloat);
    buffer->write(offset, color_vec.constData(), vertices_tmp.size() * 3 * sizeof(GLfloat));
    offset += triangles.size() * 3 * sizeof(GLfloat);
    buffer->write(offset, normal_tmp.constData(), vertices_tmp.size() * 3 * sizeof(GLfloat));
    offset += triangles.size() * 2 * sizeof(GLfloat);
    buffer->write(offset, texture_coord.constData(), vertices_tmp.size() * 3 * sizeof(GLfloat));
    buffer->release();

    if(!buffer->isCreated())
    {
        qDebug() << file_name;
    }
    vertexCount = vertices.size();
    file.close();           //zamykamy pliki *.obj
    file_mtl.close();       //i pliku *.mtl

}
void OGE::Model::Draw(QGLShaderProgram & shaderProgram, QMatrix4x4 pMatrix,QMatrix4x4 vMatrix, QMatrix4x4 mMatrix, QVector3D LightPosition)
{
    shaderProgram.bind();
    shaderProgram.setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);       //ustawiamy wartości zmiennych uniform do shadera
    shaderProgram.setUniformValue("mvMatrix", vMatrix * mMatrix);
    shaderProgram.setUniformValue("normalMatrix", mMatrix.normalMatrix());
    shaderProgram.setUniformValue("vLightPosition", LightPosition);

    buffer->bind();
    int offset = 0;
    shaderProgram.setAttributeBuffer("vertex", GL_FLOAT, offset, 3, 0);
    shaderProgram.enableAttributeArray("vertex");
    offset += vertexCount * 3 * sizeof(GLfloat);
    shaderProgram.setAttributeBuffer("color", GL_FLOAT, offset, 3, 0);
    shaderProgram.enableAttributeArray("color");
    offset += vertexCount * 3 * sizeof(GLfloat);
    shaderProgram.setAttributeBuffer("normal", GL_FLOAT, offset, 3, 0);
    shaderProgram.enableAttributeArray("normal");
    buffer->release();

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);         //rysujemy obiekt
    shaderProgram.release();
}
void OGE::Model::Draw(QGLShaderProgram & shaderProgram, QMatrix4x4 pMatrix, QMatrix4x4 vMatrix, QVector3D LightPosition)
{
    QMatrix4x4 mMatrix;

    mMatrix.translate(position);
    mMatrix.rotate(rotation.x(),1.0,0.0,0.0);
    mMatrix.rotate(rotation.y(),0.0,1.0,0.0);
    mMatrix.rotate(rotation.z(),0.0,0.0,1.0);
    shaderProgram.bind();
    shaderProgram.setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);       //ustawiamy wartości zmiennych uniform do shadera
    shaderProgram.setUniformValue("mvMatrix", vMatrix * mMatrix);
    shaderProgram.setUniformValue("normalMatrix", mMatrix.normalMatrix());
    shaderProgram.setUniformValue("vLightPosition", LightPosition);

    buffer->bind();
    int offset = 0;
    shaderProgram.setAttributeBuffer("VertexPosition", GL_FLOAT, offset, 3, 0);
    shaderProgram.enableAttributeArray("VertexPosition");
    offset += vertexCount * 3 * sizeof(GLfloat);
    shaderProgram.setAttributeBuffer("VertexColor", GL_FLOAT, offset, 3, 0);
    shaderProgram.enableAttributeArray("VertexColor");
    offset += vertexCount * 3 * sizeof(GLfloat);
    shaderProgram.setAttributeBuffer("VertexNormal", GL_FLOAT, offset, 3, 0);
    shaderProgram.enableAttributeArray("VertexNormal");
    buffer->release();

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);         //rysujemy obiekt
    shaderProgram.release();
}
void OGE::Model::SetPosition(QVector3D pos)
{
    position = pos;
}
QVector3D OGE::Model::GetPosition()
{
    return position;
}
void OGE::Model::SetRotation(QVector3D roate)
{
    rotation = roate;
}

QVector3D OGE::Model::GetRototion()
{
    return rotation;
}
void OGE::Model::Load_Assimp(QString file_name)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(file_name.toStdString().c_str(),aiProcessPreset_TargetRealtime_Quality);//aiProcessPreset_TargetRealtime_Fast has the configs you'll need
    //const aiScene *scene = new aiScene(*importer.ReadFile("models/models/Alice/Alice.DAE", aiProcessPreset_TargetRealtime_Fast));
    if( !scene)
      {
            qDebug() << importer.GetErrorString();
      }
    //aiMesh *mesh = scene->mMeshes[0]; //assuming you only want the first mesh
    //qDebug() << scene->mNumMeshes;


    QVector <QVector3D> vertices;       //wierzchołki
    QVector <QVector3D> normal;         //normalne
    QVector <QVector2D> texture_coord;  //koordynanty tekstur
    QVector <QVector3D> color;          //kolory wierzchołków
    for(int meshessnum = 0;meshessnum < scene->mNumMeshes; meshessnum++)
    {
        aiMesh *mesh = scene->mMeshes[meshessnum];
        vertexCount += mesh->mNumFaces*3;
     for(unsigned int i=0;i<mesh->mNumFaces;i++)
        {
        const aiFace& face = mesh->mFaces[i];

        //foreach index
        for(int j=0;j<3;j++)//assume all faces are triangulated
        {
            aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[j]];
            //color.push_back(QVector3D(uv.x,uv.y,uv.z));

            aiVector3D normalai = mesh->mNormals[face.mIndices[j]];
            normal.push_back(QVector3D(normalai.x,normalai.y,normalai.z));

            aiVector3D pos = mesh->mVertices[face.mIndices[j]];
            vertices.push_back(QVector3D(pos.x,pos.y,pos.z));
            if(mesh->HasVertexColors(face.mIndices[j]))
            {
                aiColor4D *colors = mesh->mColors[face.mIndices[j]];
                color.push_back(QVector3D(colors->r,colors->g,colors->b));
            }
        }
        }
    }

    //uvArray-=mesh->mNumFaces*3*2;
    //normalArray-=mesh->mNumFaces*3*3;
    //vertexArray-=mesh->mNumFaces*3*3;

    buffer = new QGLBuffer;
    buffer->create();
    buffer->bind();
    buffer->setUsagePattern(QGLBuffer::StaticDraw);
    buffer->allocate(vertices.size() * (3 + 3 + 3) * sizeof(GLfloat));      //3 współrzędne wierzchołków 3 składowe koloru i 3 składowe wektora normalnego
    int offset = 0;

    buffer->write(offset,vertices.constData(),vertices.size() * 3 * sizeof(GLfloat));
    offset += vertices.size() * 3 * sizeof(GLfloat);
    buffer->write(offset, color.constData(), vertices.size() * 3 * sizeof(GLfloat));
    offset += vertices.size() * 3 * sizeof(GLfloat);
    buffer->write(offset, normal.constData(), vertices.size() * 3 * sizeof(GLfloat));
    offset += vertices.size() * 2 * sizeof(GLfloat);
    buffer->write(offset, texture_coord.constData(), vertices.size() * 3 * sizeof(GLfloat));
    buffer->release();

    if(!buffer->isCreated())
    {
        qDebug() << file_name;
    }
    vertexCount = vertices.size();
}
