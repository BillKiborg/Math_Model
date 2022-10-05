#include "Derivative.h"

using This_Class = Derivative;

This_Class::Derivative() {
	//------------------------------	
	//------------------------------
}

void This_Class::sinus() {
	//------------------------------
	for (int i = 0; i < 360; i++) {
		qDebug() << (int)(sin((double)i / 180.0 * M_PI) * 100);
	}
	//------------------------------
}

void This_Class::set_timer(My_Timer* timer) {
	//------------------------------
	timer->installEventFilter(this);
	//------------------------------
}

//==================================

bool This_Class::eventFilter(QObject*, QEvent*) {
	//--------------------------------------------
	static bool flag = true;
	static QTime time_start;

	if (flag) {
		flag = false;
		time_start = QTime::currentTime();
	}	
	
	QTime current_T = QTime::currentTime();
	if (200 <= time_start.msecsTo(current_T)) {
		time_start = current_T;

		static int val = 0;
		//qDebug() << val << " - " << (int)(sin((float)val / 180.0 * M_PI) * 100);
		val++;
	}

	return false;
	//--------------------------------------------
}