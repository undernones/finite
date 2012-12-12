#ifndef QT_MATRIXVIEWER_H
#define QT_MATRIXVIEWER_H

#include <QWidget>
#include <Eigen>

class Ui_MatrixViewer;
class MatrixViewer : public QWidget
{
	Q_OBJECT

public:
	explicit MatrixViewer(QWidget* parent = 0);
	~MatrixViewer();

	void setMatrix(const Eigen::Matrix3d* matrix);
	const Eigen::Matrix3d* matrix() const;

    void refresh();

private:
	Ui_MatrixViewer* ui;
	const Eigen::Matrix3d* mMatrix;
};

#endif // MATRIXVIEWER_H
