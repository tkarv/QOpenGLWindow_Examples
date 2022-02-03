#ifndef CUSTOMGLWIDGET_HPP
#define CUSTOMGLWIDGET_HPP

#include <iostream>

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLPixelTransferOptions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QVideoFrame>

class CustomGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    CustomGLWidget(QWidget *parent);
//    void setTexture(const QImage &image) {
//        currentImage = image;
//    }

    void setTexture(const QVideoFrame &frame);

protected:
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void initializeGL() override;

private:
    QOpenGLVertexArrayObject vaoQuad;
    QOpenGLBuffer vboQuad;
    QOpenGLShaderProgram *shaderProgram;
    QVector<GLfloat> vertexData;

    // QImage currentImage;
    QOpenGLTexture *texture;

    void reallocateTexture(const QImage &image);
    void drawTexture(const QImage &image);

    int lastImageWidth = 0;
    int lastImageHeight = 0;
};

#endif // CUSTOMGLWIDGET_HPP
