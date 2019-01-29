#include "customglwidget.hpp"

const char* vertexSource =
        "#version 330\n"
        "layout(location = 0) in vec2 position;\n"
        "layout(location = 1) in vec3 incolor;\n"
        "out vec4 color;\n"
        "void main( void )\n"
        "{\n"
        " gl_Position = vec4(position, 0.0, 1.0);\n"
        " color = vec4(incolor, 1.0);\n"
        "}\n";

const char* fragmentSource =
        "#version 330\n"
        "in vec4 color;\n"
        "out vec4 outColor;\n"
        "void main( void )\n"
        "{\n"
        " outColor = color;\n"
        "}\n";

CustomGLWidget::CustomGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    // store triangle vertex coordinate & color data
    vertexData = { 0.0, 0.5, 1.0, 0.0, 0.0,
              0.5, -0.5, 0.0, 1.0, 0.0,
              -0.5, -0.5, 0.0, 0.0, 1.0 };
}

void CustomGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // create the shader program
    shaderProgram = new QOpenGLShaderProgram;
    bool success = shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexSource);
    if(!success) {
        std::cout << "failed!" << std::endl;
    }
    success = shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentSource);
    if(!success) {
        std::cout << "failed!" << std::endl;
    }

    // bind location for the vertex shader
    shaderProgram->bindAttributeLocation("position", 0);
    shaderProgram->link();
    shaderProgram->bind();

    // create the vertex array object
    vaoQuad.create();
    vaoQuad.bind();

    // create the vertex buffer object
    vboQuad.create();
    vboQuad.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboQuad.bind();
    vboQuad.allocate(vertexData.constData(), vertexData.count() * sizeof(GLfloat));

    // connect the inputs to the shader program
    shaderProgram->enableAttributeArray(0);
    shaderProgram->enableAttributeArray(1);
    shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 2, 5*sizeof(GLfloat));
    shaderProgram->setAttributeBuffer(1, GL_FLOAT, 2*sizeof(GLfloat), 3, 5*sizeof(GLfloat));

    QString errorLog = shaderProgram->log();

    vaoQuad.release();
    vboQuad.release();
    shaderProgram->release();

    GLenum error = glGetError();
}

void CustomGLWidget::resizeGL(int w, int h) {
    // only drawing the 2d surface so no need to modify any projections etc;
}

void CustomGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram->bind();
    vaoQuad.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    vaoQuad.release();
    shaderProgram->release();

    QString errorLog = shaderProgram->log();

    GLenum error = glGetError();
}
