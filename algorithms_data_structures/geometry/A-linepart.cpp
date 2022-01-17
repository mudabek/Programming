#include <bits/stdc++.h>

using namespace std;

class Point
{
public:
    int x;
    int y;

    Point(int x_, int y_) : x(x_), y(y_) {}
};

class Vector
{

public:
    int x;
    int y;

    explicit Vector(Point a, Point b)
    {
        x = b.x - a.x;
        y = b.y - a.y;
    }

    int dotProduct(Vector& other)
    {
        return this->x * other.x + this->y * other.y;
    }

    int crossProduct(Vector& other)
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

int main()
{
    int p_x, p_y, a_x, a_y, b_x, b_y;
    cin >> p_x >> p_y >> a_x >> a_y >> b_x >> b_y;

    Point p = Point(p_x, p_y);
    Point a = Point(a_x, a_y);
    Point b = Point(b_x, b_y);
    Vector pa = Vector(p, a);
    Vector pb = Vector(p, b);

    if (pointPartOfLine(pa, pb))
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
