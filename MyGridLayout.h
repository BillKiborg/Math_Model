#ifndef MY_GRID_LAYOUT_H
#define MY_GRID_LAYOUT_H

#include <QtWidgets>

class MyGridLayout : public QGridLayout {
public:	
	QWidget*	operator [] (QString objectName);

};

#endif
