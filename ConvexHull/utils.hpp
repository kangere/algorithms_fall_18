#pragma once

#include "point.hpp"
#include <vector>
#include <utility>

//aliases
using points_list = std::vector<point*>;
using lr_pair = std::pair<point*,point*>;

//util functions
void read_file( const char* , points_list&);
void print_file( const char* ,points_list&);


/**
	Calculates the gradient of the line formed between two points
	@param p1 point forming line
	@param p2 point forming line
**/
float get_gradient(const point* p1, const point* p2);

/**
	calculates y intercept of a line
	@param gradient - the slope of the line
	@param p - some point on the line
**/
float y_intercept(const float gradient, const point* p);

void findhull_top(points_list&, points_list&, lr_pair);

void findhull_bottom(points_list&, points_list&, lr_pair);

/**
	Determines if a point is above or below a line formed by a pair of points
	@param pair - this is the pair of two points which form the line
	@param p the point that we wish to determine is either above or
				below the line formed by the pair

	@return true if p is above the line false otherwise
**/
bool point_above(lr_pair pair,point* p);


/**
	Determines if the current point is the last point on the hull

	@param p0 the first point in the convex hull
	@param curr current point in the convex hull
	@param points a vector of all the input points
	
	@return true if the curr points to the last point on the vector
			false otherwise

**/
bool end_of_hull(point* p0,point* curr,points_list& points);
