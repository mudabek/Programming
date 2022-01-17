struct Rect
{
    int x1; int y1; // Top left point
    int x2; int y2; // Bottom right point
};

bool overlapRect(Rect r1, Rect r2) {
    //left side of one rect is to the left of another rect
    if (r1.x1 > r2.x2 || r2.x1 > r1.x2)
        return false;

    //bottom of one rect is to the top of another rect
    if (r1.y2 > r2.y1 || r1.y1 < r2.y2)
        return false;

    return true;
}
