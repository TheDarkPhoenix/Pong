#ifndef POINT_H
#define POINT_H

namespace pt
{
    class Point
    {
        public:

            float x;
            float y;

            Point(float x1, float y1);
            Point();

            Point operator =(Point p)
            {
                if (&p != this)
                {
                    x = p.x;
                    y = p.y;
                }
                return *this;
            }
            Point operator =(float f)
            {
                x = f;
                y = f;
                return *this;
            }
            Point operator *(Point p)
            {
                if (&p != this)
                {
                    x *= p.x;
                    y *= p.y;
                }
                return *this;
            }
            Point operator *(float f)
            {
                Point p = *this;
                p.x *= f;
                p.y *= f;
                return p;
            }
            Point operator +=(Point p)
            {
                if (&p != this)
                {
                    x += p.x;
                    y += p.y;
                }
                return *this;
            }
            Point operator +=(int i)
            {
                x += i;
                y += i;
                return *this;
            }
    };

    Point PointMake(float x, float y);
}
#endif
