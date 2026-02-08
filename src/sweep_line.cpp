#include <algorithm>
#include <geom/Lines.h>
#include <geom/Point.h>
using namespace geom;

struct event {
	int type;
	Point point;
	LineSegment segment;
	event(int type, Point point, LineSegment segment) : type(type), point(point), segment(segment) {}
};

	struct node {
		LineSegment segment;
		node* left;
		node* right;
		node(LineSegment segment) : segment(segment), left(nullptr), right(nullptr) {}
	};

void sweepLine() {
	LineSegment segments[] = {
		{{0, 0}, {1, 1}},
		{{0, 1}, {1, 0}},
		{{0.5, 0}, {0.5, 1}}
	};
	// start point = type 1
	// end point = type 2
	// intersection point = type 3

	// Vector of events  
	std::vector<event> events;  

	// Add events to the vector  
	for (const auto& segment : segments) {  
	    events.emplace_back(1, segment.start, segment); // Start point  
	    events.emplace_back(2, segment.end, segment);   // End point  
	}  

	// Sort events based on the y-coordinate, and if equal, by type (start before end)  this uses a lambda function for comparison
	std::sort(events.begin(), events.end(), [](const event& a, const event& b) {  
	    if (a.point.y != b.point.y)  
	        return a.point.y < b.point.y;  
	    return a.type < b.type;  
	});  

	for (const auto& e : events) {  
		if (e.type == 1) {  
			// Handle start point: add segment to active set  
		} else if (e.type == 2) {  
			// Handle end point: remove segment from active set  
		} else {  
			// Handle intersection point: report intersection and update active set  
		}  
	}

	// This function will implement the sweep line algorithm
	// It will use the event structure and binary search tree to manage the active segments

	//add events to the event queue
	
	//process events in order

}