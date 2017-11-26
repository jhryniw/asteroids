#include "common.h"

#define IN_RANGE(X, A, B) (X >= A && X <= B)

bool on_screen(int x, int y)
{
    return IN_RANGE(x, 0, TFT_WIDTH) && IN_RANGE(y, 0, TFT_HEIGHT);
}

#undef IN_RANGE

//
bool rayTraceEdge(point centroid, edge e, point p) {
	// Based on https://rosettacode.org/wiki/Ray-casting_algorithm
	int max_x = max(e.p1.x, e.p2.x)+centroid.x;
	//int min_x = min(e.p1.px, e.p2.px);
	int max_y = max(e.p1.y, e.p2.y)+centroid.y;
	int min_y = min(e.p1.y, e.p2.y)+centroid.y;

	return p.x > max_x && p.y < max_y && p.y > min_y;
}

// Returns if a point and a closed polygon are colliding
bool is_collision(point p, polygon poly)
{
    int intersections = 0;

	for (int i = 0; i < poly.nedges; i++) {
		if (rayTraceEdge(poly.centroid, poly.edges[i], p)) {
			intersections++;
		}
	}

	return intersections % 2 == 1;
}
