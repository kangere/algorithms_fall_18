#include "utils.hpp"


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <utility>
#include <iterator>

/**
	Calculates distance from point to line

	@param p_l point on line
	@param p_r point on line
	@param p point to calculate distance from

**/
static
double distance(point* p_l, point* p_r, point* p)
{
	int num = std::abs(((p_r->get_y() - p_l->get_y()) * p->get_x()) - 
					((p_r->get_x() - p_l->get_x()) * p->get_y()) +
					(p_r->get_x() * p_l->get_y()) - (p_r->get_y() * p_l->get_x()));

	double denom = std::sqrt(std::pow(p_r->get_y() - p_l->get_y(), 2) + std::pow(p_r->get_x() - p_l->get_x(), 2));

	return static_cast<double>(num) / denom; 
}


float get_gradient(const point* p1, const point* p2)
{
	return (static_cast<float>(p2->get_y() - p1->get_y()) 
			/ static_cast<float>(p2->get_x() - p1->get_x())); 
}


float y_intercept(const float gradient, const point* p)
{
	return (p->get_y() - (gradient * p->get_x()));
}


void read_file(const char* filename, points_list &points)
{
	std::fstream file(filename,std::ios::in);

	if(file.is_open())
	{
		while(!file.eof())
		{
			std::string line;
			std::getline(file,line);

			std::istringstream ss(line);
			
			int num1,num2;
			ss >> num1 >> num2;

			points.push_back(new point(num1,num2));

		}
	}
	else
	{
		std::cout << "Could not open file!" << std::endl;
	}

	file.close();
}

void print_file(const char* filename, points_list& hull)
{
	std::fstream out(filename,std::ios::out);

	if(out.is_open()){

		for(point* p : hull)
			out << *p << std::endl;
		
	} else {
		std::cerr << "Unable to open file" << std::endl;
	}

	out.close();
}

//Finds points on hull that are on the top of the line formed
//by the leftmost and righmost points
void findhull_top(points_list& hull, points_list& sub, lr_pair lr_p)
{
	if(sub.size() < 1)
		return;
	else if(sub.size() == 1){
		auto i = std::find(hull.begin(),hull.end(),lr_p.first);
		hull.insert(i+1,sub.back());
		return;
	}

	point* leftmost = lr_p.first;
	point* rightmost = lr_p.second;

	//iterator to farthest point
	auto iter = std::max_element(sub.begin(),sub.end(),
				[leftmost,rightmost](point* p1, point* p2)
				{
					return distance(leftmost,rightmost,p1) < distance(leftmost,rightmost,p2);

				});

	point* farthest_p = *iter;

	//insert point in between leftmost and righmost points
	auto it = std::find(hull.begin(),hull.end(),leftmost);
	hull.insert(it+1,farthest_p);

	//structures to store points
	//either right or left of triangle
	//formed by the leftmost, rightmost and farthest points
	points_list right;
	points_list left;


	//find left points
	float gradient_l = get_gradient(lr_p.first,farthest_p);
	float y_int_l  = y_intercept(gradient_l,farthest_p);

	std::copy_if(sub.begin(),sub.end(),std::back_inserter(left),
				[gradient_l,y_int_l](point* p)
				{
					return p->get_y() > ((gradient_l * p->get_x()) + y_int_l);
				});


	//find right points
	float gradient_r = get_gradient(farthest_p,lr_p.second);
	float y_int_r  = y_intercept(gradient_r,farthest_p);

	std::copy_if(sub.begin(),sub.end(),std::back_inserter(right),
				[gradient_r,y_int_r](point* p)
				{
					return p->get_y() > ((gradient_r * p->get_x()) + y_int_r);
				});

	//recursively process outer points
	findhull_top(hull,left,std::make_pair(lr_p.first, farthest_p));

	findhull_top(hull,right,std::make_pair(farthest_p,lr_p.second));
}


//Finds points on hull that are on the bottom of the line formed
//by the leftmost and righmost points
void findhull_bottom(points_list& hull, points_list& sub, lr_pair lr_p)
{
	if(sub.size() < 1)
		return;
	else if(sub.size() == 1){
		auto i = std::find(hull.begin(),hull.end(),lr_p.first);
		hull.insert(i+1,sub.back());
		return;
	}

	point* leftmost = lr_p.first;
	point* rightmost = lr_p.second;
	
	//iterator to farthest point
	auto iter = std::max_element(sub.begin(),sub.end(),
				[leftmost,rightmost](point* p1, point* p2)
				{
					return distance(leftmost,rightmost,p1) < distance(leftmost,rightmost,p2);

				});

	point* farthest_p = *iter;

	//insert point in between left and righmost points
	auto it = std::find(hull.begin(),hull.end(),leftmost);
	hull.insert(it+1,farthest_p);

	//structures to store points
	//either right or left of triangle
	//formed by the leftmost, rightmost and farthest points
	points_list right;
	points_list left;


	//find left points
	float gradient_l = get_gradient(lr_p.first,farthest_p);
	float y_int_l  = y_intercept(gradient_l,farthest_p);

	std::copy_if(sub.begin(),sub.end(),std::back_inserter(left),
				[gradient_l,y_int_l](point* p)
				{
					return p->get_y() < ((gradient_l * p->get_x()) + y_int_l);
				});


	//find right points
	float gradient_r = get_gradient(farthest_p,lr_p.second);
	float y_int_r  = y_intercept(gradient_r,farthest_p);

	std::copy_if(sub.begin(),sub.end(),std::back_inserter(right),
				[gradient_r,y_int_r](point* p)
				{
					return p->get_y() < ((gradient_r * p->get_x()) + y_int_r);
				});

	//recursively process outer points
	findhull_bottom(hull,left,std::make_pair(lr_p.first, farthest_p));

	findhull_bottom(hull,right,std::make_pair(farthest_p,lr_p.second));
}

bool point_above(lr_pair pair,point* p)
{
	float gradient = get_gradient(pair.first,pair.second);
	float y_int  = y_intercept(gradient,pair.first);

	return p->get_y() > ((gradient * p->get_x()) + y_int);

}

bool end_of_hull(point* p0, point* curr,points_list& points)
{
	points_list points_left;

	for(auto p : points){
		if(p == p0 || p == curr)
			continue;
		else if(!point_above(std::make_pair(p0,curr),p))
			points_left.push_back(p);	
	}

	return points_left.size() == 0;
}