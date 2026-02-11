#include "geom/Lines.h"
#include <limits>
#include <algorithm> 

namespace geom {

    Point find_intersection(const LineSegment& seg1, const LineSegment& seg2) {
        // Extract line equations
        const Line& line1 = seg1.line;
        const Line& line2 = seg2.line;

        // Check if either line is undefined
        if (std::isnan(line1.a) || std::isnan(line2.a)) {
            return Point(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN());
        }

        // Check if lines are parallel
        if (line1.a == line2.a) {
            return Point(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN());
        }

        // Calculate intersection point
        double x, y;
        if (std::isinf(line1.a)) { // Line1 is vertical
            x = line1.b;
            y = line2.a * x + line2.b;
        }
        else if (std::isinf(line2.a)) { // Line2 is vertical
            x = line2.b;
            y = line1.a * x + line1.b;
        }
        else {
            x = (line2.b - line1.b) / (line1.a - line2.a);
            y = line1.a * x + line1.b;
        }

        // Check if the intersection point lies within both segments
        if (x < std::min(seg1.start.x, seg1.end.x) || x > std::max(seg1.start.x, seg1.end.x) ||
            x < std::min(seg2.start.x, seg2.end.x) || x > std::max(seg2.start.x, seg2.end.x) ||
            y < std::min(seg1.start.y, seg1.end.y) || y > std::max(seg1.start.y, seg1.end.y) ||
            y < std::min(seg2.start.y, seg2.end.y) || y > std::max(seg2.start.y, seg2.end.y)) {
            return Point(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN());
        }

        return Point(x, y);
    }

}