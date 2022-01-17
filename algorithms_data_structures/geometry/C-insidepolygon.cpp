#include <bits/stdc++.h>

using namespace std;

const double PI = 3.14159265358979323846;
const double EPS = 1e-8;

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

bool pointPartOfLine(Vector& pa, Vector& pb)
{
    if (pa.dotProduct(pb) > 0)
        return false;

    if (pa.crossProduct(pb) == 0)
        return true;

    return false;
}

bool areEqual(double a, double b)
{
    return fabs(a - b) < EPS;
}

double getAngle(Vector v1, Vector v2)
{
    double angle = atan2(v2.y, v2.x) - atan2(v1.y, v1.x);

    while (angle > PI)
    {
        angle -= 2 * PI;
    }
    while (angle < -PI)
    {
        angle += 2 * PI;
    }
    return angle;
}

bool pInsidePolygon(vector<Point> points, Point p)
{
    double angle;
    double sum = 0;
    int len = points.size();

    for (int i = 0; i < len; ++i)
    {
        Vector pa = Vector(p, points[i]);
        Vector pb = Vector(p, points[(i + 1) % len]);
        if (pointPartOfLine(pa, pb))
            return true;
        angle = getAngle(pa, pb);
        sum += angle;
    }

    if (areEqual(abs(sum), 2 * PI))
        return true;

    return false;
}

int main()
{
    int temp_x, temp_y, vertCount;

    cin >> vertCount >> temp_x >> temp_y;

    Point p = Point(temp_x, temp_y);

    vector<Point> points;

    for (int i = 0; i < vertCount; ++i)
    {
        cin >> temp_x >> temp_y;
        points.push_back(Point(temp_x, temp_y));
    }

    if (pInsidePolygon(points, p))
        cout << "YES";
    else
        cout << "NO";

    return 0;
}
