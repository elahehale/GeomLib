#include <geom/point.h>

double geom::euclidean_dist(const Point& a, const Point& b)
{
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}
