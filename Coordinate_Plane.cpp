#include "Coordinate_Plane.h"

using This_Class = Coordinate_Plane;

This_Class::Coordinate_Plane() {
	//------------------------------------------
	setWindowTitle("Coordinate Plane");
	setMinimumSize(1081, 436);
	show();

	timer = new My_Timer;
	timer->installEventFilter(this);

	Coordinate_Standart::set_center({ 266, 318 });
	//------------------------------------------
}

void This_Class::marking(QPainter* painter) {
	//------------------------------------------
	auto center = Coordinate_Standart::center();	

	coordinate
		axle_X = { size().width(), center.y },
		axle_Y = { center.x, 0 },
		axle_x = { 0, center.y },
		axle_y = { center.x, size().height() };

	painter->setPen(QPen(Qt::black, 3));
	painter->drawLine(center.x, center.y, axle_X.x, axle_X.y);
	painter->drawLine(center.x, center.y, axle_Y.x, axle_Y.y);
	painter->drawLine(center.x, center.y, axle_x.x, axle_x.y);
	painter->drawLine(center.x, center.y, axle_y.x, axle_y.y);

	painter->setPen(QPen(Qt::black, 1));
	for (int x = center.x + 10; x < size().width(); x += 10) {
		coordinate
			S1 = { x, center.y + 5 },
			S2 = { x, center.y - 5 };

		painter->drawLine(S1.x, S1.y, S2.x, S2.y);
	}

	for (int y = center.y - 10; 0 <= y; y -= 10) {
		coordinate
			S1 = { center.x + 5, y },
			S2 = { center.x - 5, y };

		painter->drawLine(S1.x, S1.y, S2.x, S2.y);
	}

	for (int x = center.x - 10; 0 <= x; x -= 10) {
		coordinate
			S1 = {x, center.y + 5},
			S2 = {x, center.y - 5};

		painter->drawLine(S1.x, S1.y, S2.x, S2.y);
	}

	for (int y = center.y + 10; y < size().height(); y += 10) {
		coordinate
			S1 = { center.x + 5, y },
			S2 = { center.x - 5, y };

		painter->drawLine(S1.x, S1.y, S2.x, S2.y);
	}
	//------------------------------------------
}

void This_Class::lined(QPainter* painter) {
	//------------------------------------------
	coordinate center = Coordinate_Standart::center();

	painter->setPen(QPen(QColor(172, 229, 238), 0));
	for (int x = center.x + 10; x < size().width(); x += 10) {
		coordinate
			M1 = { x, 0 },
			M2 = { x, size().height() };

		painter->drawLine(M1.x, M1.y, M2.x, M2.y);
	}

	for (int y = center.y - 10; 0 <= y; y -= 10) {
		coordinate
			M1 = { 0, y },
			M2 = { size().width(), y };

		painter->drawLine(M1.x, M1.y, M2.x, M2.y);
	}

	for (int x = center.x - 10; 0 <= x; x -= 10) {
		coordinate
			M1 = { x, 0 },
			M2 = { x, size().height() };

		painter->drawLine(M1.x, M1.y, M2.x, M2.y);
	}

	for (int y = center.y + 10; y < size().height(); y += 10) {
		coordinate
			M1 = { 0, y },
			M2 = { size().width(), y };

		painter->drawLine(M1.x, M1.y, M2.x, M2.y);
	}
	//------------------------------------------
}

void This_Class::mooving_coordinates(QMouseEvent* mE) {
	//------------------------------------------
	int
		shift_x,
		shift_y;

	if (!start_shift){
		start_shift = new QPoint(
			mE->pos()
		);
	}	
	
	shift_x = mE->x() - start_shift->x();
	shift_y = mE->y() - start_shift->y();

	*start_shift = mE->pos();

	coordinate center = Coordinate_Standart::center();
	Coordinate_Standart::set_center(
		{ center.x + shift_x, center.y + shift_y }
	);
	//------------------------------------------
}

void This_Class::draw_derivative(QPainter* painter) {
	//------------------------------------------------
	painter->setPen(QPen(QColor(3, 192, 60), 5));

	const float delta_X = 0.1;
	float current_X = (float)point_dev.x;
	float current_Y = (float)point_dev.y;
	
	float derivative = (sin(((current_X + delta_X) / 180.0 * M_PI) / 1) - sin((current_X / 180.0 * M_PI) / 1)) / delta_X;
	float angle = atanf((derivative * 1000));	

	coordinate
		D1 = { (cos(angle) * 100) + current_X, (sin(angle) * 100) + current_Y },
		D2 = { (cos(M_PI + angle) * 100) + current_X, (sin(M_PI + angle) * 100) + current_Y };	

	D1 = Coordinate_Standart::transform_to(D1, type_coordinate::monitor);
	D2 = Coordinate_Standart::transform_to(D2, type_coordinate::monitor);

	point_dev = Coordinate_Standart::transform_to(point_dev, type_coordinate::monitor);		
	
	painter->drawLine(D1.x, D1.y, D2.x, D2.y);
	//------------------------------------------------
}

void This_Class::draw_sinus(QPainter* painter) {
	//------------------------------------------
	painter->setPen(QPen(Qt::red, 5));

	static bool		flag = true;
	QPoint			arr[1440];

	for (int i = -720; i < 720; i++) {
		arr[720 + i] = { i, (int)(sin(((float)i / 180.0 * M_PI) / 1) * 170) };
	}
	
	for (auto& e : arr) {
		coordinate _coordinate = Coordinate_Standart::transform_to(
			{ e.x(), e.y()}, type_coordinate::monitor
		);

		e.setX(_coordinate.x);
		e.setY(_coordinate.y);
	}

	painter->drawPolyline(arr, 1439);
	
	//------------------------------------------
}

//=================================================

void This_Class::paintEvent(QPaintEvent*) {
	//------------------------------------------
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	lined(&painter);
	marking(&painter);	
	draw_sinus(&painter);
	draw_derivative(&painter);

	painter.end();
	//------------------------------------------
}

void This_Class::mousePressEvent(QMouseEvent* mE) {
	//------------------------------------------
	coordinate _coordinate = Coordinate_Standart::transform_to(
		{ mE->pos().x(), mE->pos().y() },
		type_coordinate::relative
	);

	qDebug() << _coordinate.x << " - " << _coordinate.y;
	mooving_coordinates(mE);
	update();
	//------------------------------------------
}

void This_Class::mouseMoveEvent(QMouseEvent* mE) {
	//------------------------------------------
	mooving_coordinates(mE);
	update();
	//------------------------------------------
}

void This_Class::mouseReleaseEvent(QMouseEvent*) {
	//------------------------------------------
	delete start_shift;
	start_shift = nullptr;
	update();
	//------------------------------------------
}

bool This_Class::eventFilter(QObject*, QEvent* qE) {
	//------------------------------------------
	if (qE->type() == QEvent::Timer) {

		static QTime starting_point = QTime::currentTime();

		if (10 <= starting_point.msecsTo(QTime::currentTime())) {
			starting_point = QTime::currentTime();

			static int cntr		= -180;
			coordinate point	= { cntr, (int)(sin(((float)cntr / 180.0 * M_PI) / 1) * 170)};

			point_dev = point;
			update();

			cntr++;

			if (cntr == 720) cntr = -180;
		}
	}

	return false;
	//------------------------------------------
}
