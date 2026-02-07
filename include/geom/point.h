#include <math.h>
#pragma once
// Using namespace geom to aoid conflicts with other
// libraries (if they have structs like Point)

namespace geom {


	// Simple 2D point structure
	struct Point {
		double x{}, y{};
		// Add a constructor to allow initialization with two doubles
		Point(double x_val, double y_val) : x(x_val), y(y_val) {}
	};


	// Calculate Euclidean distance between two points by calling 
	// with references to avoid copying
	double euclidean_dist(const Point& a, const Point& b);
	
	//PerpendicularBisector perpendicular_bisector(const Point& a, const Point& b);
}