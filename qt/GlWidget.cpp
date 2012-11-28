#include "GlWidget.h"
#include <GLUT/glut.h>
#include <QtGui/QMouseEvent>

namespace
{
const double SPHERE_SIZE = 0.015;
const double WIRE_OFFSET = 0.0005;
const unsigned MAX_UINT = std::numeric_limits<unsigned>::max();
}

GlWidget::GlWidget(QWidget* parent) :
    QGLWidget(parent),
    mRotX(0.f), mRotY(0.f)
{
    mLightPos[0] = 0.0f;
    mLightPos[1] = 2.0f;
    mLightPos[2] = 9.0f;
    mLightPos[3] = 1.0f;

    mLightColor[0] = 1.f;
    mLightColor[1] = 1.f;
    mLightColor[2] = 1.f;

    mLightAmb[0] = 0.09f;
    mLightAmb[1] = 0.09f;
    mLightAmb[2] = 0.09f;

    mEye = Eigen::Vector3d(0, 0, 1.1);
    mLookAt = Eigen::Vector3d(0, 0, 0);
}

GlWidget::~GlWidget()
{
}

void
GlWidget::initializeGL()
{
    glClearDepth(1.0f);

    glEnable(GL_CULL_FACE);
    glEnable(GL_POLYGON_SMOOTH);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_POINT_SMOOTH);
    glPointSize(5.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // lighting

    glLightfv(GL_LIGHT0, GL_POSITION, mLightPos);
    glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, mLightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  mLightColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, mLightColor);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  mLightAmb);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    {
        GLfloat mat[3] = { 0.2f, 0.2f, 0.2f };
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat);

        mat[0] = 0.7f; mat[1] = 0.7f; mat[2] = 0.7f;
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);

        mat[0] = 0.1f; mat[1] = 0.1f; mat[2] = 0.1f;
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
        glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
    }

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, mLightAmb);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

    initSphereList();
}

void
GlWidget::resizeGL(int w, int h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLdouble)w / (GLdouble)h, 0.01, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(mEye[0], mEye[1], mEye[2], mLookAt[0], mLookAt[1], mLookAt[2], 0, 1, 0);
}

void
GlWidget::paintGL()
{
    glClearColor(0.03f, 0.03f, 0.03f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(mEye[0], mEye[1], mEye[2], mLookAt[0], mLookAt[1], mLookAt[2], 0, 1, 0);

    glRotatef(mRotX, 1.0f, 0, 0);
    glRotated(mRotY, 0, 1.0f, 0);

    // Draw stuff!

    glColor3d(0, 0, 0.9);
    glBegin(GL_QUADS);
    glVertex3d(0, 0, 0);
    glVertex3d(10, 0, 0);
    glVertex3d(10, 10, 0);
    glVertex3d(0, 10, 0);
    glEnd();

    glFlush();
}

void
GlWidget::mousePressEvent(QMouseEvent* event)
{
    mLastMouse = event->pos();

    if ((event->buttons() & Qt::LeftButton) && !(event->modifiers() & Qt::ControlModifier)) {
        // Select a particle
        //unsigned selected = select(mLastMouse);
        //select(selected);
    }
}

void
GlWidget::mouseReleaseEvent(QMouseEvent*)
{
}

void
GlWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint dp = event->pos() - mLastMouse;

    double scale, len, theta;
    Eigen::Vector3d neye, neye2;
    Eigen::Vector3d f, r, u;

    if ((event->buttons() & Qt::LeftButton) && (event->modifiers() & Qt::ControlModifier)) {
        // translate
        f = mLookAt - mEye;
        u = Eigen::Vector3d(0, 1, 0);

        // scale the change by how far away we are
        scale = sqrt(f.norm()) * 0.007;

        r = f.cross(u).normalized();
        u = r.cross(f).normalized();

        mEye += (-r * dp.x() * scale) + (u * dp.y() * scale);
        mLookAt += (-r * dp.x() * scale) + (u * dp.y() * scale);

    } else if (event->buttons() & Qt::MidButton) {
        zoom(dp.x());

    } else if (event->buttons() & Qt::RightButton) {
        // rotate

        neye = mEye - mLookAt;

        // first rotate in the x/z plane
        theta = -dp.x() * 0.007;
        neye2 = Eigen::Vector3d(
            cos(theta) * neye[0] + sin(theta) * neye[2],
            neye[1],
            -sin(theta) * neye[0] + cos(theta) * neye[2]
        );


        // now rotate vertically
        theta = -dp.y() * 0.007;

        f = -neye2;
        u = Eigen::Vector3d(0, 1, 0);
        r = f.cross(u).normalized();
        u = r.cross(f).normalized();
        len = f.norm();
        f.normalize();

        neye = len * (((float)cos(theta) * f) + ((float)sin(theta) * u));

        mEye = mLookAt - neye;
    }

    mLastMouse = event->pos();

    this->repaint();
}

void
GlWidget::wheelEvent(QWheelEvent* event)
{
    int delta = event->delta();
    zoom(delta);
    this->repaint();
}

void
GlWidget::initSphereList()
{
    mSphereSolid = glGenLists(2);
    mSphereWire = mSphereSolid + 1;

    glNewList(mSphereSolid, GL_COMPILE);
    glutSolidSphere(SPHERE_SIZE, 20, 20);
    glEndList();

    glNewList(mSphereWire, GL_COMPILE);
    glutWireSphere(SPHERE_SIZE + WIRE_OFFSET, 20, 20);
    glEndList();
}

void
GlWidget::zoom(int delta)
{
    Eigen::Vector3d f = mLookAt - mEye;
    double len = f.norm();
    f.normalize();

    // scale the change by how far away we are
    len -= sqrt(len) * delta * 0.01;

    mEye = mLookAt - (len * f);

    // make sure the eye and lookat points are sufficiently far away
    // push the lookat point forward if it is too close
    if (len < 1) {
        mLookAt = mEye + f;
    }
}
 
