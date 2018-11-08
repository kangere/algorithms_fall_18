#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <tuple>
#include <chrono>


#include "point.hpp"
#include "utils.hpp"


using points_list = std::vector<point*>;


void graham_scan(points_list&);
void jarvis_march(points_list&);
void quickhull(points_list&);




int main(int argc, char const *argv[])
{
	if(argc < 3 || argc > 3)
	{
		std::cout << "Wrong number of arguments, i.e to run program type: \"hull G filename\"" << std::endl;
		std::cout << "where 'G' determines algorithm chosen, and 'filename' is the name of input file" << std::endl;
	} else {
		points_list points;

		read_file(argv[2],points);

		std::cout << "Reading points from file..." << std::endl;
		
		std::string algo;

		if(*argv[1] == 'G'){
			graham_scan(points);
			algo = "Graham scan";	
		}
		else if(*argv[1] == 'J'){
			jarvis_march(points);
			algo = "Jarvis march";
		}
		else if(*argv[1] == 'Q'){
			quickhull(points);	
			algo = "Quick hull";	
		}

		std::cout << "Algorithm chosen: " << algo << std::endl;


	}
	

	return 0;
}


void graham_scan(points_list& points)
{
	if(points.size() < 3)
		return;
	else if(points.size() == 3){
		print_file("hull_G.txt",points);
		return;
	}

	auto start = std::chrono::high_resolution_clock::now();
	//find p0
	auto min_y = std::min_element(points.begin(), points.end(),
				[] (point* const p1, point* const p2)
				{
					if(p1->get_y() == p2->get_y())
						return p1->get_x() < p2->get_x();
					
					return p1->get_y() < p2->get_y();
				});

	point* p0 = *min_y;

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
	

	//vector holding points on hull
	points_list hull;

	//push 1st three points to stack
	for(int i = 0; i < 3; i++)
		hull.push_back(points[i]);

	//iterate over sorted points
	//pop depending on vector direction
	for(int i = 3; i < points.size(); i++)
	{

		point* v1 = find_vect(hull[hull.size() - 2],hull.back());
		point* v2 = find_vect(hull.back(), points[i]);

		while(vec_direction(v1,v2) <= 0){
			hull.pop_back();
			
			v1 = find_vect(hull[hull.size() - 2],hull.back());
			v2 = find_vect(hull.back(), points[i]);
		}
			
		hull.push_back(points[i]);
	}

	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Execution time: " << duration.count()<< " microseconds" << std::endl;

	print_file("hull_G.txt",hull);
}

void jarvis_march(points_list& points)
{
	if(points.size() < 3)
		return;
	else if(points.size() == 3){
		print_file("hull_J.txt",points);
		return;
	}

	auto start = std::chrono::high_resolution_clock::now();
	//find left most point
	point* p0 = *(std::min_element(points.begin(),points.end(),
					[](point* p1, point* p2){
						return p1->get_x() < p2->get_x(); 
					}));
	

	points_list hull;

	hull.push_back(p0);

	for(size_t i = 0; i < points.size(); i++)
	{
		
		point* curr = hull.back();
		point* v1 = find_vect(curr,new point(curr->get_x(),curr->get_y()+2));

		float polar = 0.0;
		point* hull_point = nullptr;

		point* v2 = nullptr;

		if(end_of_hull(p0,curr,points))
			break;

		for(auto point : points)
		{
			if(std::find(hull.begin(), hull.end(),point) != hull.end())
				continue;

			// v2 = find_vect(curr,point);
			

			if(polar == 0){
				polar = polar_angle(curr,point);
				hull_point = point;
			} else {
				float new_polar = polar_angle(curr,point);

				if(new_polar < polar)
				{
					polar = new_polar;
					hull_point = point; 
				}
			}

			
		}

		if(hull_point)
			hull.push_back(hull_point);
	}

	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

	print_file("hull_J.txt",hull);
}


void quickhull(points_list& points)
{
	if(points.size() < 3)
		return;
	else if(points.size() == 3){
		print_file("hull_Q.txt",points);
		return;
	}

	auto start = std::chrono::high_resolution_clock::now();

	

	std::vector<point*> hull;

	point *leftmost_x, *rightmost_x;

	auto minmax = std::minmax_element(points.begin(),points.end(),
										[](point* const p1, point* const p2)
										{
												return p1->get_x() < p2->get_x();
										});

	std::tie(leftmost_x,rightmost_x) = std::make_tuple(*minmax.first,*minmax.second);



	std::cout << "leftmost: " <<*leftmost_x << " rightmost: " << *rightmost_x << std::endl; 

	//add points to hull
	hull.push_back(leftmost_x);
	hull.push_back(rightmost_x);

	//find gradient and y-intercept of line formed from points above
	float gradient = get_gradient(leftmost_x,rightmost_x);
	float y_int  = y_intercept(gradient,leftmost_x);

	//create vectors to store points
	//either above or below the line formed from points above
	std::vector<point*> above_l;
	std::vector<point*> below_l;

	
	std::for_each(points.begin(), points.end(),
						[gradient, y_int, leftmost_x, rightmost_x, &above_l, &below_l](point* p){

							if(p!= leftmost_x && p!= rightmost_x){
								if(p->get_y() > ((gradient * p->get_x()) + y_int))
									above_l.push_back(p);
								else
									below_l.push_back(p);	
							}
							
						});

	//find top half points on hull
	findhull_top(hull,above_l,std::make_pair(leftmost_x,rightmost_x));

	//find bottom half points on hull
	findhull_bottom(hull,below_l,std::make_pair(leftmost_x,rightmost_x));

	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

	print_file("hull_Q.txt",hull);

}


