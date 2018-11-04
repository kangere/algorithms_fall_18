#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>


#include "point.hpp"


void graham_scan(std::vector<point*>&);
void jarvis_march(std::vector<point*>&);
void read_file(std::string, std::vector<point*>&);
void print_file(std::string, std::vector<point*>&);



int main(int argc, char const *argv[])
{
	std::vector<point*> points;

	read_file("test.txt",points);

	std::cout << "Points read from file:" << std::endl;
	for(auto p : points)
		p->print();

	// graham_scan(points);

	jarvis_march(points);

	return 0;
}


void graham_scan(std::vector<point*> &points)
{
	//find p0
	point *p0 = points[0];

	for(int i = 1; i < points.size(); i++)
	{
		point *p = points[i];

		//if same y
		if(p0->get_y() == p->get_y())
		{
			if(p->get_x() < p0->get_x())
				p0 = p;
		}
		else if(p->get_y() < p0->get_y())
			p0 = p;	
	}

	std::cout << "p0 is " << *p0 << "\n";

	//sort points 
	std::sort(points.begin(),points.end(),[p0](point* p1, point* p2){

		if(p1 == p0)
			return true;
		if(p2 == p0)
			return false;
		if(p1 == p2)
			return true;

		point* p1_v = find_vect(p0,p1);
		point* p2_v = find_vect(p0,p2);

		return (p1_v->get_x() * p2_v->get_y()) > (p1_v->get_y() * p2_v->get_x());
	});
	
	
	std::cout << " Sorted points " << std::endl;
	for(auto point : points)
		point->print();

	//vector holding points on hull
	std::vector<point*> hull;

	//push 1st three points to stack
	for(int i = 0; i < 3; i++)
		hull.push_back(points[i]);

	//iterate over sorted points
	//pop depending on vector direction
	for(int i = 3; i < points.size(); i++)
	{

		point* v1 = find_vect(hull[hull.size() - 2],hull.back());
		point* v2 = find_vect(hull.back(), points[i]);

		while(vec_direction(v1,v2) < 0){
			hull.pop_back();
			
			v1 = find_vect(hull[hull.size() - 2],hull.back());
			v2 = find_vect(hull.back(), points[i]);
		}
			
		hull.push_back(points[i]);
	}

	std::cout << "convex hull points" << std::endl;
	for(auto point : hull)
		point->print();

}

void jarvis_march(std::vector<point*>& points)
{
	//find left most point
	point* p0 = points[0];

	for(auto point : points)
	{
		if(point->get_x() < p0->get_x())
			p0 = point;
	}

	std::vector<point*> hull;

	hull.push_back(p0);

	for(size_t i = 0; i < points.size(); i++)
	{
		
		point* curr = hull.back();
		point* v1 = find_vect(curr,new point(curr->get_x(),curr->get_y()+2));

		float polar = 0.0;
		point* hull_point = nullptr;

		point* v2 = nullptr;

		for(auto point : points)
		{
			if(std::find(hull.begin(), hull.end(),point) != hull.end())
				continue;

			v2 = find_vect(curr,point);
			

			if(polar == 0){
				polar = polar_angle(v1,v2);
			} else {
				if(polar_angle(v1,v2) < polar)
				{
					polar = polar_angle(v1,v2);
					hull_point = point; 
				}
			}

			
		}

		if(hull_point)
			hull.push_back(hull_point);
	}

	for(auto point : hull)
		point->print();
}


void read_file(std::string filename, std::vector<point*> &points)
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
}