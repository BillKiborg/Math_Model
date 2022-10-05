#ifndef COORDINATE_PLANE_H
#define COORDINATE_PLANE_H

#include <QtWidgets>
#include "My_Timer.h"
#include "Coordinate_Standart.h"
#include "Derivative.h"

//======================================
class Coordinate_Plane : public QLabel {
	Q_OBJECT
private:
	My_Timer*	timer				= nullptr;
	QPoint*		start_shift			= nullptr;

	coordinate	point_dev = { 0, 0 };

protected:
	void paintEvent		(QPaintEvent*)		override;
	void mousePressEvent(QMouseEvent*)		override;
	void mouseMoveEvent	(QMouseEvent*)		override;
	void mouseReleaseEvent(QMouseEvent*)	override;

	bool eventFilter(QObject*, QEvent*)		override;

public:
	Coordinate_Plane();
	void marking(QPainter*);
	void lined	(QPainter*);
	void mooving_coordinates(QMouseEvent*);

	void draw_sinus(QPainter*);
	void draw_derivative(QPainter*);
	
};
//======================================

#endif
