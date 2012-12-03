#ifndef QT_GLWIDGET_H
#define QT_GLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <Eigen>

class Mesh;
class GlWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GlWidget(QWidget* parent = NULL);
    ~GlWidget();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void wheelEvent(QWheelEvent*);

    void setMesh(const Mesh* mesh) { mMesh = mesh; }

private:
    GLfloat mLightPos[4];
    GLfloat mLightAmb[3];
    GLfloat mLightColor[3];

    Eigen::Vector3d mEye;
    Eigen::Vector3d mLookAt;
    QPoint mLastMouse;

    GLfloat mRotX;
    GLfloat mRotY;

    GLuint mSphereSolid;
    GLuint mSphereWire;

    const Mesh* mMesh;

    void initSphereList();
    void zoom(int delta);

    void renderGeometry() const;
};

#endif // QT_GLWIDGET_H
