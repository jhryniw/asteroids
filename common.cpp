#include "common.h"

#define IN_RANGE(X, A, B) (X >= A && X <= B)

bool on_screen(int x, int y)
{
    return IN_RANGE(x, 0, TFT_WIDTH) && IN_RANGE(y, 0, TFT_HEIGHT);
}

#undef IN_RANGE

//
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

	/*
	Serial.println("-");
	Serial.print("x1: ");
	Serial.print(e.p1.x);
	Serial.print(" y1: ");
	Serial.print(e.p1.y);
	Serial.print(" x2: ");
	Serial.print(e.p2.x);
	Serial.print(" y2: ");
	Serial.println(e.p2.y);
	Serial.print("a1: ");
	Serial.print(a1);
	Serial.print(" b1: ");
	Serial.print(b1);
	Serial.print(" c1: ");
	Serial.print(c1);
	Serial.print(" a2: ");
	Serial.print(a2);
	Serial.print(" b2: ");
	Serial.print(b2);
	Serial.print(" c2: ");
	Serial.print(c2);
	Serial.print(" det: ");
	Serial.println(det);
	Serial.print("tx: ");
	Serial.print(tx);
	Serial.print(" ty: ");
	Serial.print(ty);
	Serial.print(" max x: ");
	Serial.println(x_threshold);
	Serial.println("-");
	*/
    return tx >= x_min;
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
