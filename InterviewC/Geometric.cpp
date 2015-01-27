#include <vector>
#include <algorithm>

/*****************************************************************************/

struct Point {
	int x, y;
	double distance(const Point &p) {
		int dx = this->x - p.x, dy = this->y - p.y;
		return std::sqrt(dx * dx + dy * dy);
	}
};

typedef std::vector<Point> Points;

double closest_base(
	Points &points,
	double min = std::numeric_limits<double>::max()) {
	double cmin = min;

	for (auto i = points.begin(); i != points.end(); ++i)
		for (auto j = i + 1; j != points.end() && i->distance(*j) < min; ++j)
			cmin = std::min(cmin, i->distance(*j));

	return cmin;
}

double closest_sorted(Points &px, Points &py) {
	// Base case.
	if (px.size() <= 3) return closest_base(px);

	// Horizontally divide points into equal halves.
	Points::size_type mid = px.size() / 2;
	Points pxl = Points(px.begin(), px.begin() + mid);
	Points pxr = Points(px.begin() + mid + 1, px.end());
	Points pyl, pyr;
	for (Point p : py) {
		if (p.x <= py[mid].x) pyl.push_back(p);
		else pyr.push_back(p);
	}

	// Recurse to get left and right closest distance.
	double dl = closest_sorted(pxl, pyl);
	double dr = closest_sorted(pxr, pyr);
	double dlr = std::min(dl, dr);

	// Find smallest distance across halves.
	Points strip;
	for (Point p : py) {
		double dist = std::abs(p.x - px[mid].x);
		if (dist < dlr) strip.push_back(p);
	}
	double d = closest_base(strip, dlr);

	// Return overall minimum.
	d = std::min(d, dlr);
	return d;
}

double closest(const Points &points) {
	// Sort points by x and y coordinates.
	Points px = points, py = points;

	std::sort(px.begin(), px.end(), [](Point p1, Point p2) { return p1.x < p2.x; });
	std::sort(px.begin(), px.end(), [](Point p1, Point p2) { return p1.y < p2.y; });

	return closest_sorted(px, py);
}

/*****************************************************************************/