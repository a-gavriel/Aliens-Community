#ifndef _GRAPH_POINTS_H_
#define _GRAPH_POINTS_H_

typedef struct Point { 
    float x; 
    float y; 
} Point;

const Point A_in [32] ;

const Point A_out [24] ;

const Point A_top_left [12] ;

const Point A_top_center [5];

const Point A_top_right [12];

const Point B_top_left [12];

const Point B_top_center [5];

const Point B_top_right [11];

//const Point bridge_left [];

//const Point bridge_center [];

//const Point bridge_right [];

const Point A_bottom_left [9];

const Point A_bottom_center [4];

const Point A_bottom_right [11];

const Point B_bottom_left [9];

const Point B_bottom_center [4];

const Point B_bottom_right [10];

const Point B_in [32];

const Point B_out [23];

const int routes_sizes[19];

const Point *routes_coords[19];



#endif