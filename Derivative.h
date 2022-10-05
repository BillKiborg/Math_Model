#ifndef DERIVATIVE_H
#define DERIVATIVE_H

#include <QtWidgets>
#include "My_Timer.h"

class Derivative : public QWidget {
private:
	

protected:
	bool eventFilter(QObject*, QEvent*) override;

public:
	Derivative();
	void sinus();
	void set_timer(My_Timer*);

};

#endif

