#include "MyGridLayout.h"

QWidget* MyGridLayout::operator [] (QString objectName) {
	//---------------------------------------------------
	for (int i = 0; i < this->count(); i++) {

		if (auto wgt = this->itemAt(i)->widget()) {

			if (wgt->objectName() == objectName) {

				return wgt;
			}
		}
	}
	
	return nullptr;
}