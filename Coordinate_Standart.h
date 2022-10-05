#ifndef COORDINATE_STANDART_H
#define COORDINATE_STANDART_H

struct coordinate {
	int x;
	int y;
};

enum type_coordinate {
	monitor,
	relative
};

//======================================
class Coordinate_Standart {
private:
	static coordinate coordinate_center;
public:	
	static void set_center(coordinate center);
	static coordinate center();
	static coordinate transform_to(coordinate, type_coordinate _type_coordinate);
};
//======================================

#endif

