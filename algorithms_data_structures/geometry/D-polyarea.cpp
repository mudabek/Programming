#include <bits/stdc++.h>

using namespace std;

class Point
{
public:
    long long x;
    long long y;

    Point(int x_, int y_) : x(x_), y(y_) {}
};

class Vector
{
public:
    long long x;
    long long y;

    explicit Vector(Point a, Point b)
    {
        x = b.x - a.x;
        y = b.y - a.y;
    }

    long long dotProduct(Vector& other)
    {
        return this->x * other.x + this->y * other.y;
    }

    long long crossProduct(Vector& other)
    {
        return this->x * other.y - this->y * other.x;
    }
};

double halfPolyArea(vector<Point>& points, int n)
{
    double ans = 0.0;
    Point p = Point(points[0].x, points[0].y);
    for (int i = 1; i < n - 1; ++i)
    {
        Point p1 = Point(points[i].x, points[i].y);
        Point p2 = Point(points[i + 1].x, points[i + 1].y);
        Vector v1 = Vector(p, p1);
        Vector v2 = Vector(p, p2);
        ans += v1.crossProduct(v2);
    }
    return fabs(ans);
}

int main()
{
    int temp_x, temp_y, vertCount;

    cin >> vertCount;

    vector<Point> points;

    for (int i = 0; i < vertCount; ++i)
    {
        cin >> temp_x >> temp_y;
        points.push_back(Point(temp_x, temp_y));
    }

    cout << fixed << setprecision(3) << halfPolyArea(points, vertCount) / 2;

    return 0;
}
