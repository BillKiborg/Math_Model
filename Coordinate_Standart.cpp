#include "Coordinate_Standart.h"

using This_Class = Coordinate_Standart;

coordinate This_Class::coordinate_center = { 0, 0 };

void This_Class::set_center(coordinate center) {
    //---------------------------------------------
    coordinate_center = center;
    //---------------------------------------------
}

coordinate This_Class::center() {
    //---------------------------------------------
    return coordinate_center;
    //---------------------------------------------
}

coordinate This_Class::transform_to(coordinate _coordinate, type_coordinate _type_coordinate) {
    //---------------------------------------------
    switch (_type_coordinate) {
    case type_coordinate::monitor:
        
        _coordinate = {
            _coordinate.x + coordinate_center.x,
            coordinate_center.y - _coordinate.y
        };
        
        return _coordinate;
        break;

    case type_coordinate::relative:

        _coordinate = { 
            _coordinate.x - coordinate_center.x,
            coordinate_center.y - _coordinate.y 
        };

        return _coordinate;
        break;
    }
    //---------------------------------------------
}