#include <math.h>
// Using namespace geom to aoid conflicts with other
// libraries (if they have structs like Point)

namespace geom {


	// Simple 2D point structure
	struct Point {
		double x{}, y{};
	};


	// Calculate Euclidean distance between two points by calling 
	// with references to avoid copying
	double euclidean_dist(const Point& a, const Point& b);
	
	geom::Point, double, double perpendicular_bisector(const Point& a, const Point& b);
}