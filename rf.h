#ifndef RF_H
#define RF_H

#include "vec.h"

struct RectF
{
    Vector2f origin;    //Левый нижний угол
    Vector2f size;      //

    RectF() = default;

    RectF(double x,double y, double width, double height)
        :origin(x,y),size(width,height)
    {
    }

    float leftEdge() const
    {
        return origin.x;
    }

    float rightEdge() const
    {
        return origin.x + size.x;
    }

    float topEdge() const
    {
        return origin.y;
    }

    float bottomEdge() const
    {
        return origin.y + size.y;
    }
};

#endif // RF_H
