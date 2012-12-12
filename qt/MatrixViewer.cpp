#include "MatrixViewer.h"
#include "ui_MatrixViewer.h"

using Eigen::Matrix3d;

MatrixViewer::MatrixViewer(QWidget* parent) :
    QWidget(parent),
    ui(new Ui_MatrixViewer),
    mMatrix(NULL)
{
    ui->setupUi(this);
    setMatrix(NULL);
}

MatrixViewer::~MatrixViewer()
{
    delete ui;
}

void
MatrixViewer::setMatrix(const Matrix3d* matrix)
{
    mMatrix = matrix;
    refresh();
}

const Matrix3d*
MatrixViewer::matrix() const
{
    return mMatrix;
}

void
MatrixViewer::refresh()
{
    if (mMatrix != NULL)
    {
        static const char format = 'f';

        const Matrix3d& m = *mMatrix;
        ui->label00->setText(QString("%1").arg(m(0, 0), 0, format, 4));
        ui->label10->setText(QString("%1").arg(m(1, 0), 0, format, 4));
        ui->label20->setText(QString("%1").arg(m(2, 0), 0, format, 4));
        ui->label01->setText(QString("%1").arg(m(0, 1), 0, format, 4));
        ui->label11->setText(QString("%1").arg(m(1, 1), 0, format, 4));
        ui->label21->setText(QString("%1").arg(m(2, 1), 0, format, 4));
        ui->label02->setText(QString("%1").arg(m(0, 2), 0, format, 4));
        ui->label12->setText(QString("%1").arg(m(1, 2), 0, format, 4));
        ui->label22->setText(QString("%1").arg(m(2, 2), 0, format, 4));

        ui->labelDeterminant->setText(QString("Determinant: %1").arg(m.determinant()));
    }
    else
    {
        ui->label00->setText(tr("NA"));
        ui->label10->setText(tr("NA"));
        ui->label20->setText(tr("NA"));
        ui->label01->setText(tr("NA"));
        ui->label11->setText(tr("NA"));
        ui->label21->setText(tr("NA"));
        ui->label02->setText(tr("NA"));
        ui->label12->setText(tr("NA"));
        ui->label22->setText(tr("NA"));

        ui->labelDeterminant->setText("Determinant: NA");
    }
}
