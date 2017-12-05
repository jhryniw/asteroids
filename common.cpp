#include "common.h"

#define IN_RANGE(X, A, B) (X >= A && X <= B)

// Check if a point is on the screen
bool on_screen(int x, int y)
{
    return IN_RANGE(x, 0, TFT_WIDTH) && IN_RANGE(y, 0, TFT_HEIGHT);
}

#undef IN_RANGE

// Does the raytracing calculation
bool rayTraceEdge(point centroid, edge e, point p) {
    /*
		Ray casting based on
		https://rosettacode.org/wiki/Ray-casting_algorithm
		Line intersection based on
		https://www.topcoder.com/community/data-science/data-science-tutorials/
		geometry-concepts-line-intersection-and-its-applications/
	*/

	float tx = p.x - centroid.x;
	float ty = p.y - centroid.y;

	if (e.p1.y == e.p2.y || tx < min(e.p1.x, e.p2.x) ||
		ty > max(e.p1.y, e.p2.y) || ty < min(e.p1.y, e.p2.y)) {
			return false;
	}

	if (tx > max(e.p1.x, e.p2.x)) {
		return true;
	}

	float a1 = e.p2.y - e.p1.y;
	float b1 = e.p1.x - e.p2.x;
	float c1 = a1 * e.p1.x + b1 * e.p1.y;

	// float a1 = 0;
	float b2 = -tx;
	float c2 = b2 * ty;

	float det = a1 * b2;

	// since parallel lines return false, det != 0
	float x_min = (b2 * c1 - b1 * c2) / det;

    return tx >= x_min;
}

// Returns if a point and a closed polygon are colliding
bool is_collision(point p, polygon poly)
{
    int intersections = 0;

	for (int i = 0; i < poly.sides; i++) {
		if (rayTraceEdge(poly.centroid, poly.edges[i], p)) {
			intersections++;
		}
	}

	return intersections % 2 == 1;
}
