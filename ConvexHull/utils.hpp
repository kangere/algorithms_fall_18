#pragma once

#include "point.hpp"
#include <vector>
#include <utility>

//alias long names
using points_list = std::vector<point*>;
using lr_pair = std::pair<point*,point*>;

//util functions
void read_file(const char* filename, std::vector<point*>&);
void print_file(const char* filename, const points_list&);
float get_gradient(const point*, const point*);
float y_intercept(const float, const point*);

void findhull_top(points_list&, points_list, lr_pair);

void findhull_bottom(points_list&, points_list, lr_pair);
