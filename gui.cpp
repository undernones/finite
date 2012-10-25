#include <iostream>
#include <Eigen>
#include "gls.h"
#include "Options.h"
#include "World.h"

using Eigen::Vector3d;
using Eigen::Vector4d;

// Globals
int gMainWnd;
GLfloat gLightPos[] = { 0, 10, 10, 1 };
GLfloat gLightColor[] = { 1, 1, 1 };
GLfloat gLightAmbient[] = { 0.09, 0.09, 0.09 };
float gRotX = 0;
float gRotY = 0;
int gMouseX = -1;
int gMouseY = -1;
int gLastX;
int gLastY;
int gCurrentButton = -1;
Vector3d gEye;
Vector3d gLookAt;

// Glut Fuctions
GLvoid initGl();
GLvoid redraw();
GLvoid resize(GLsizei width, GLsizei height);
GLvoid idle();
GLvoid mouseButton(int button, int state, int x, int y);
GLvoid mouseDrag(int x, int y);

GLvoid
initGl()
{
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glClearColor(0.1, 0.1, 0.1, 0);
    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glLightfv(GL_LIGHT0, GL_POSITION, gLightPos);
    glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, gLightPos);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat mat[3] = { 0.2, 0.2, 0.2 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);

    mat[0] = 0.7; mat[1] = 0.7; mat[2] = 0.7;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);

    mat[0] = 0.1; mat[1] = 0.1; mat[2] = 0.1;
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT, GL_SHININESS, 128);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gLightAmbient);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

    glEnable(GL_POINT_SMOOTH);
    glPointSize(4);
}


GLvoid
redraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    gluLookAt(gEye[0], gEye[1], gEye[2], gLookAt[0], gLookAt[1], gLookAt[2], 0, 1, 0);
    glRotatef(gRotX, 1, 0, 0);
    glRotatef(gRotY, 0, 1, 0);

    glLightfv(GL_LIGHT0, GL_POSITION, gLightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, gLightColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, gLightColor);
    glLightfv(GL_LIGHT0, GL_AMBIENT, gLightAmbient);

    // Draw points
    glColor3d(0.8, 0, 0);
    glBegin(GL_POINTS);
    for (const Vertex& v : World::mesh().verts) {
        glVertex3d(v.x[0], v.x[1], v.x[2]);
    }
    glEnd();

    glColor3d(0.8, 0.8, 0.8);
    glBegin(GL_LINES);
    for (const Vertex& v : World::mesh().verts) {
        Vector3d end = v.x + v.f;
        glVertex3d(v.x[0], v.x[1], v.x[2]);
        glVertex3d(end[0], end[1], end[2]);
    }
    glColor3d(0, 0.8, 0);
    for (const Tetrahedron& t : World::mesh().tets) {
        const Vector3d* norms = t.normals();
        for (int i = 0; i < 4; ++i) {
            glVertex3d(0, 0, 0);
            glVertex3d(norms[i][0], norms[i][1], norms[i][2]);
        }
    }
    glEnd();


    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

GLvoid
resize(GLsizei width, GLsizei height)
{
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (GLdouble)width / (GLdouble)height, 0.01, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(gEye[0], gEye[1], gEye[2], gLookAt[0], gLookAt[1], gLookAt[2], 0, 1, 0);

    glutPostRedisplay();
}

GLvoid
idle()
{
    static uint32_t totalSteps = Options::duration() / Options::dt();
    static uint32_t i = 0;
    if (i < totalSteps) {
        World::step(Options::dt());
        i++;
        glutPostRedisplay();
    }
}

GLvoid
mouseButton(int button, int state, int x, int y)
{
    switch (state) {
    case GLUT_DOWN:
        gCurrentButton = button;
        break;

    default:
        gCurrentButton = -1;
        break;
    }

    gLastX = x;
    gLastY = y;
}

GLvoid
mouseDrag(int x, int y)
{
    int dx = x - gLastX;
    int dy = y - gLastY;

    double scale, len, theta;
    Vector3d neye, neye2;
    Vector3d f, r, u;

    switch (gCurrentButton) {
    case GLUT_LEFT_BUTTON:
        // translate
        f = gLookAt - gEye;
        u = Vector3d(0, 1, 0);

        scale = sqrt(f.norm()) * 0.007;

        r = f.cross(u);
        u = r.cross(f);
        r.normalize();
        u.normalize();

        gEye += (-r * dx * scale) + (u * dy * scale);
        gLookAt += (-r * dx * scale) + (u * dy * scale);
        break;

    case GLUT_MIDDLE_BUTTON:
        // zoom
        f = gLookAt - gEye;

        len = f.norm();
        f.normalize();

        // scale the change by how far away we are.
        len -= sqrt(len) * dx * 0.03;
        gEye = gLookAt - (len * f);

        // make sure the eye and look-at points are sufficiently far away
        // push the look-at point forward if it is too close
        if (len < 1) {
            std::cout << "Look-at move: " << len << std::endl;
            gLookAt = gEye + f;
        }
        break;

    case GLUT_RIGHT_BUTTON:
        // rotate
        neye = gEye - gLookAt;

        // first rotate in the x/z plane
        theta = -dx * 0.007;
        neye2 = Vector3d(cos(theta) * neye[0] + sin(theta) * neye[2],
                         neye[1],
                        -sin(theta) * neye[0] + cos(theta) * neye[2]);
    }

    gLastX = x;
    gLastY = y;
    glutPostRedisplay();
}

int
main(int argc, char* argv[])
{
    Options::init(&argc, &argv);
    World::init(Options::meshFile());

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    gMainWnd = glutCreateWindow("Finite Elements GUI");

    initGl();

    glutDisplayFunc(redraw);
    glutReshapeFunc(resize);
    glutIdleFunc(idle);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseDrag);

    gEye = Vector3d(0, 2, 4);
    gLookAt = Vector3d(0, 0, 0);

    glutMainLoop();
    return 0;
}
