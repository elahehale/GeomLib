#include "point.h"
namespace geom {
	struct Line {
		double a{};
		double b{};
	};

	struct PerpendicularBisector{
		Line line;
		Point midpoint;
	};

	struct LineSegment {
		Point start;
		Point end;
	};

	struct SupportedLine {
		Line line;
		LineSegment segment;
	};
}