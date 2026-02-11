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
	geom::LineSegment segment2;
	event() : type(0), point(0, 0), segment() {} // Default constructor added
	event(int type, Point point, geom::LineSegment segment) : type(type), point(point), segment(segment) {}
	event(int type, Point point, geom::LineSegment segment, geom::LineSegment segment2) : type(type), point(point), segment(segment), segment2(segment) {}

};


int y = 12;
struct CustomComparator {
	bool operator()(const geom::LineSegment& a, const geom::LineSegment& b) const {
		std::cout << y << std::endl;
		return ((y - a.line.b) / a.line.a) > ((y - b.line.b) / b.line.a); // Reverse order (greater than)
	}
};


struct EventComparator {
	bool operator()(const event& a, const event& b) const {

		// 1?? Sort by y (ascending)
		if (a.point.y != b.point.y)
			return a.point.y < b.point.y;

		// 2?? If y equal ? smaller x first
		if (a.point.x != b.point.x)
			return a.point.x < b.point.x;

		// 3?? If x equal ? smaller type first (1 < 2 < 3)
		if (a.type != b.type)
			return a.type < b.type;

		// If all equal ? they are considered equal
		return false;
	}
};



int handle_start_event(const event& e, BalancedBinaryTree<geom::LineSegment, CustomComparator>& tree, BalancedBinaryTree<event, EventComparator>& Q) {
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
		Point intersection = find_intersection(parent, e.segment);
		if (!std::isnan(intersection.x) && !std::isnan(intersection.y)) {
			std::cout << "Intersection found at: (" << intersection.x << ", " << intersection.y << ")" << std::endl;
			Q.insert(event{ 3, intersection, parent, e.segment });
		}
		else {
			std::cout << "No intersection found between parent and current segment." << std::endl;
		}
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
	BalancedBinaryTree<event, EventComparator> Q;

	// insert initial events
	for (const auto& segment : segments) {
		Q.insert(event{ 1, segment.start, segment });
		Q.insert(event{ 2, segment.end, segment });
	}

	// process in descending y


	BalancedBinaryTree<geom::LineSegment, CustomComparator> tree;


	event e;
	while (Q.popMax(e)) {
		y = e.point.y; // Update the global y-coordinate for the comparator
		if (e.type == 1) {
			handle_start_event(e, tree, Q);
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
	BalancedBinaryTree<LineSegment, CustomComparator> tree;
	Point p1(1, 2), p2(3, 4);
	LineSegment line1{ p1, p2 };
	tree.insert(line1);
	std::cout << "Inserted line segment: (" << line1.start.x << ", " << line1.start.y << ") to ("
		<< line1.end.x << ", " << line1.end.y << ")" << std::endl;
	y = 20; // Change the value of y to see the effect in the comparator
	Point p3(7, 8), p4(4, 4);
	LineSegment line2{ p3, p4 };
	tree.insert(line2);
	std::cout << "Inserted line segment";
	return 0;
}