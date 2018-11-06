#pragma once

#include "point.hpp"
#include <vector>
#include <utility>

//util functions
void read_file(std::string, std::vector<point*>&);
void print_file(std::string, std::vector<point*>&);
float get_gradient(const point*, const point*);
float y_intercept(const float, const point*);

void findhull_top(std::vector<point*>&,std::vector<point*>, std::pair<point*,point*>);

void findhull_bottom(std::vector<point*>&,std::vector<point*>, std::pair<point*,point*>);
