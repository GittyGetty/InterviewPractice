#include <algorithm>
#include <iostream>
#include <vector>
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

struct Building { int left, height, right; };
struct Strip { int left, height; };
typedef std::vector<Strip> Skyline;
typedef std::vector<Building> Buildings;
void append(Skyline &sl, Strip &s) {
    if (!sl.empty()) {
        Strip b = sl.back();
        // Gaps between buildings count as zero height.
        if (b.height == s.height) return;
        if (b.left == s.left) {
            // Assumes that higher buildinds with same left
            // are always wider.
            b.height = std::max(b.height, s.height);
            return;
        }
    }
    sl.push_back(s);
}
Skyline merge(Skyline &sl, Skyline &sr) {
    Skyline r;
    int hl = 0, hr = 0;
    size_t li = 0, ri = 0;
    while (li < sl.size() && ri < sr.size()) {
        if (sl[li].left < sr[ri].left) {
            hl = sl[li].height;
            append(r, Strip{ sl[li].left, std::max(hl, hr) });
            li++;
        } else {
            hr = sr[ri].height;
            append(r, Strip{ sr[ri].left, std::max(hl, hr) });
            ri++;
        }
    }
    for (Strip s : sl) append(r, s);
    for (Strip s : sr) append(r, s);
    return r;
}
Skyline skyline(Buildings &b, size_t l, size_t r) {
    if (l == r) {
        Skyline s;
        append(s, Strip{ b[l].left, b[l].height });
        append(s, Strip{ b[l].right, 0 });
        return s;
    }
    size_t mid = (l + r) / 2;
    return merge(skyline(b, l, mid), skyline(b, mid + 1, r));
}
Skyline skyline(Buildings &b) {
    return skyline(b, 0, b.size() - 1);
}
void skyline_test() {
    Buildings b;
    Skyline s;
    b = {
            { 1, 11, 5 },
            { 2, 6, 7 },
            { 3, 13, 9 },
            { 12, 7, 16 },
            { 14, 3, 25 },
            { 19, 18, 22 },
            { 23, 13, 29 },
            { 24, 4, 28 },
    };
    s = skyline(b);
    b = {
            { 1, 11, 2 },
            { 5, 11, 6 },
    };
    s = skyline(b);
    b = {
            { 1, 20, 3 },
            { 1, 10, 2 },
    };
    s = skyline(b);
}
/*****************************************************************************/