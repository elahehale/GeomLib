#include <algorithm>
#include <geom/Lines.h>
#include <geom/Point.h>
#include <vector>
#include <iostream>
#include "geom/BBST.h"
using std::vector;
using namespace geom;

struct event {
	int type;
	Point point;
	geom::LineSegment segment;
	event(int type, Point point, geom::LineSegment segment) : type(type), point(point), segment(segment) {}
};

	struct node {
		geom::LineSegment segment;
		node* left;
		node* right;
		node(geom::LineSegment segment) : segment(segment), left(nullptr), right(nullptr) {}
	};


int y = 12;
struct CustomComparator {
	bool operator()(const geom::LineSegment& a, const geom::LineSegment& b) const {
		std::cout << y << std::endl;
		return ((y - a.line.b) / a.line.a) > ((y - b.line.b) / b.line.a); // Reverse order (greater than)
	}
};

int handle_start_event(const event& e, BalancedBinaryTree<geom::LineSegment, CustomComparator>& tree) {
	std::cout << "Handling start event for segment: (" << e.segment.start.x << ", " << e.segment.start.y << ") to ("
		<< e.segment.end.x << ", " << e.segment.end.y << ")" << std::endl;
	tree.insert(e.segment);
	geom::LineSegment parent;
	bool notRoot = tree.getParent(e.segment, parent); // pass parent as pointer, not reference
	geom::LineSegment child1, child2;
	bool children = tree.getChildren(e.segment, child1, child2); // pass child1/child2 as pointers
	if (notRoot) {
		std::cout <<"this is not root, parent is: (" << parent.start.x << ", " << parent.start.y << ") to ("
			<< parent.end.x << ", " << parent.end.y << ")" << std::endl;
	}
	else {
		std::cout << "this is root" << std::endl;
	}
	if (children) {
		std::cout << "child 1: (" << child1.start.x << ", " << child1.start.y << ") to ("
			<< child1.end.x << ", " << child1.end.y << ")" << std::endl;
		std::cout << "child 2: (" << child2.start.x << ", " << child2.start.y << ") to ("
			<< child2.end.x << ", " << child2.end.y << ")" << std::endl;
	}
	else {
		std::cout << "not found" << std::endl;
	}
	return 0;
}
void sweepLine() {
	geom::LineSegment segments[] = {
		{{4, 5}, {5, 4}},
		{{5, 6}, {4, 2}},
		{{5, 3}, {4, 1}},
		{{5, 7}, {3, 0}},
	};

	// start point = type 1
	// end point = type 2
	// intersection point = type 3

	// Vector of events  
	vector<event> events;

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

	BalancedBinaryTree<geom::LineSegment, CustomComparator> tree;


	for (const auto& e : events) {
		if (e.type == 1) {
			handle_start_event(e, tree);
			// Handle start point: add segment to active set  
		}
		else if (e.type == 2) {
			// Handle end point: remove segment from active set  
		}
		else {
			// Handle intersection point: report intersection and update active set  
		}
	}

	// This function will implement the sweep line algorithm
	// It will use the event structure and binary search tree to manage the active segments

	//add events to the event queue

	//process events in order

}

int test_bbst()
{
	std::cout << y << std::endl;
	BalancedBinaryTree<geom::LineSegment, CustomComparator> tree;
	geom::Point p1(1, 2), p2(3, 4);
	geom::LineSegment line1{ p1, p2 };
	tree.insert(line1);
	std::cout << "Inserted line segment: (" << line1.start.x << ", " << line1.start.y << ") to ("
		<< line1.end.x << ", " << line1.end.y << ")" << std::endl;
	y = 20; // Change the value of y to see the effect in the comparator
	geom::Point p3(7, 8), p4(4, 4);
	geom::LineSegment line2{ p3, p4 };
	tree.insert(line2);
	std::cout << "Inserted line segment";
	return 0;
}