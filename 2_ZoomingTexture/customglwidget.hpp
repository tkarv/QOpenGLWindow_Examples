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
#include <QKeyEvent>

class CustomGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    CustomGLWidget(QWidget *parent);
    void setTexture(const QImage &image) {
        currentImage = image;
    }

protected:
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void initializeGL() override;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QOpenGLVertexArrayObject vaoQuad;
    QOpenGLBuffer vboQuad;
    QOpenGLShaderProgram *shaderProgram;
    QVector<GLfloat> vertexData;

    QImage currentImage;
    QOpenGLTexture *texture;

    bool zoom;
};

#endif // CUSTOMGLWIDGET_HPP
