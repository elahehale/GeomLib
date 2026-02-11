#include "point.h"
#include <limits> 
#include <cmath>
#pragma once
namespace geom {
	struct Line {
		double a{};
		double b{};
	};

	struct PerpendicularBisector{
		Line line;
		geom::Point midpoint;
	};

	struct LineSegment {
		Point start;
		Point end;
		Line line;

		LineSegment() : start(0, 0), end(0, 0) { updateLine(); }
		LineSegment(const Point& s, const Point& e) : start(s), end(e) { updateLine(); }

		void updateLine() {
			// identical points -> undefined line
			if (start.x == end.x && start.y == end.y) {
				line.a = std::numeric_limits<double>::quiet_NaN();
				line.b = std::numeric_limits<double>::quiet_NaN();
				return;
			}

			// vertical line -> represent as a = +inf, b = x
			if (start.x == end.x) {
				line.a = std::numeric_limits<double>::infinity();
				line.b = start.x;
				return;
			}

			// standard slope-intercept
			line.a = (end.y - start.y) / (end.x - start.x); // slope
			line.b = start.y - line.a * start.x;           // intercept
		}
	};
	Point find_intersection(const LineSegment& seg1, const LineSegment& seg2);

}