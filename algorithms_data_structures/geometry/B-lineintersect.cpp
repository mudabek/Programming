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

bool pointPartOfLine(Vector& pa, Vector& pb)
{
    if (pa.dotProduct(pb) > 0)
        return false;

    if (pa.crossProduct(pb) == 0)
        return true;

    return false;
}

bool lineIntersect(Point a, Point b, Point c, Point d)
{
    Vector ab = Vector(a, b);
    Vector ac = Vector(a, c);
    Vector ad = Vector(a, d);
    Vector cd = Vector(c, d);
    Vector ca = Vector(c, a);
    Vector cb = Vector(c, b);
    Vector da = Vector(d, a);
    Vector db = Vector(d, b);
    Vector bc = Vector(b, c);
    Vector bd = Vector(b, d);

    long long firstCheck = ab.crossProduct(ac) * ab.crossProduct(ad);
    long long secondCheck = cd.crossProduct(ca) * cd.crossProduct(cb);


    if (firstCheck <= 0 && secondCheck <= 0)
    {
        if (ab.crossProduct(ac) == 0 && ab.crossProduct(ad) == 0 &&
            cd.crossProduct(ca) == 0 && cd.crossProduct(cb) == 0)
            if (!pointPartOfLine(ca, cb) && !pointPartOfLine(da, db) &&
                !pointPartOfLine(ac, ad) && !pointPartOfLine(bc, bd))
                return false;
        return true;
    }
    return false;
}

int main()
{
    long long a_x, a_y, b_x, b_y, c_x, c_y, d_x, d_y;

    cin >> a_x >> a_y >> b_x >> b_y;
    cin >> c_x >> c_y >> d_x >> d_y;

    Point a = Point(a_x, a_y);
    Point b = Point(b_x, b_y);
    Point c = Point(c_x, c_y);
    Point d = Point(d_x, d_y);

    if (lineIntersect(a, b, c, d))
        cout << "YES";
    else
        cout << "NO";

    return 0;
}
